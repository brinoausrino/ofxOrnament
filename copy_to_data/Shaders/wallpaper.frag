#version 120
#extension GL_ARB_texture_rectangle : enable

#define PI 3.141592653589793

#define RECTANGLE 0
#define SQUARE 1
#define RHOMBIC 2
#define HEXAGONAL 3
#define OBLIQUE 4



uniform sampler2DRect 	u_tex_unit0;
uniform float           tex_width,tex_height;
uniform float 			width,height;
uniform int 			cell_structure;
						/*
						0 = RECTANGLE,
    					1 = SQUARE,
    					2 = RHOMBIC,
    					3 = HEXAGONAL,
    					4 = OBLIQUE
    					*/
uniform float 			tile_size;
uniform float			angle;



vec2 p1,p2,p3,p4;
vec2 base1,base2,base3,base4;
vec2 nextCellSouth, nextCellEast, nextCellNorth, nextCellWest;

/*****************
* Transformation *
******************/
float map(float val,float inMin,float inMax,float outMin,float outMax){
    return outMin + ((outMax - outMin) / (inMax - inMin)) * (val - inMin);
}

float fmod(float val, float modulo){
    int i = int(val/modulo);
    return val - (i*modulo);
}

vec2 translate(vec2 point ,vec2 trans){
	return point + trans;
}

vec2 rotate(vec2 point, float angle){
	mat2 rot = mat2 (
		cos(angle), sin(angle),
		-sin(angle),cos(angle));
	return rot * point;
}

vec2 rotateAt(vec2 point, vec2 anchor, float angle){
	return vec2(
		cos(angle)*point.x - sin(angle)*point.y + anchor.x - cos(angle)*anchor.x + sin(angle)*anchor.y,
		sin(angle)*point.x + cos(angle)*point.y + anchor.y - sin(angle)*anchor.x - cos(angle)*anchor.y);
}

vec2 reflectAt(vec2 point, vec2 anchor, vec2 dir){
	vec2 I = point-anchor;
	vec2 N = normalize(dir);
	vec2 r = reflect(I,N);
	return anchor - r;
}

bool PointInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2)
{
    float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
    float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

    if ((s < 0) != (t < 0))
        return false;

    float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;
    if (A < 0.0)
    {
        s = -s;
        t = -t;
        A = -A;
    }
    return s > 0 && t > 0 && (s + t) < A;
}

/************************
 * Position calculation *
 ************************/

void updateCornerPoints(){
    float w = tex_width;
    float h = tex_height;

        if (cell_structure == RECTANGLE)
        {
            p1 = vec2(0, 0);
            p2 = vec2(w, 0);
            p3 = vec2(w, h);
            p4 = vec2(0, h);
        }
        else if (cell_structure == SQUARE)
        {
            float length = min(w, h);
            p1 = vec2((w-length)/2, (h-length)/2);
            p2 = vec2((w-length)/2 + length, (h-length)/2);
            p3 = vec2((w-length)/2 + length, (h-length)/2 + length);
            p4 = vec2((w-length)/2, (h-length)/2 + length);
        }
        else if (cell_structure == RHOMBIC)
        {
            p1 = vec2(w/2,0);
            p2 = vec2(w,h/2);
            p3 = vec2(w/2,h);
            p4 = vec2(0,h/2);
        }
        else if (cell_structure == OBLIQUE)
        {
            float length_side = 0.5;
            float l = w*(1-length_side);
            p1 = vec2(l,0);
            p2 = vec2(w,0);
            p3 = vec2(w-l,h);
            p4 = vec2(0,h);
        }
        else if (cell_structure == HEXAGONAL)
        {
            float hmax = w*sqrt(3)/3;
            float wmax = w;
            
            if (hmax>h) {
                hmax = h;
                wmax = hmax*3/sqrt(3);
            }
            
            p1 = vec2(wmax*1/3,0);
            p2 = vec2(wmax,0);
            p3 = vec2(wmax*2/3,hmax);
            p4 = vec2(0,hmax);
        }
    
}

vec2 do_square(vec2 pos){

    //startpos
    float px = pos.x;
    float py = pos.y;

    //coord 0,0 to center
    float dx = (px - width/2);
    float dy = (py - height/2);

    //tile coordinate
    px = fmod(dx,tile_size);
    py = fmod(dy,tile_size);

    if (px<0) px = tile_size + px;
    if (py<0) py = tile_size + py;
    
    //map to global texure coordinate
    px = map(px,0,tile_size,p1.x,p3.x);
    py = map(py,0,tile_size,p1.y,p4.y-1);

    px = fmod(px, p3.x);
    
    return vec2(px,py); 
}

vec2 do_hexagonal(vec2 pos){
    //tile dimensions
    float tWidth = tile_size;
    float tHeight = tWidth*p4.y/p3.x;

    //startpos
    float px = pos.x;
    float py = pos.y;

    //coord 0,0 to center
    float dx = (px - width/2);
    //if(dx<0) dx += width;
    float dy = (py - height/2);//+height;
    //if(dy<0) dy += height;

    //dx = px;
    //dy = py;
    //number of line of current tile
    float nlF = dy/tHeight;
    if (nlF<0) nlF -= 1;
    int nline = int(nlF);

    //tile coordinate
    px = fmod(dx,tWidth);
    py = fmod(dy,tHeight);

    if (px<0) px = tWidth + px;
    if (py<0) py = tHeight + py;

    //if(px<=0) px += tWidth;

    //map to global texure coordinate
    px = map(px,0,tWidth,0,p3.x);
    py = map(py,0,tHeight,1,p4.y-1);
    
    //translation for following lines
    if(nline>0){
        px = px + nline*p1.x;
    }
    else{ 
        px = px + 2*p1.x + (p1.x*nline*-1);
    }
    
    px = fmod(px, p3.x);
    
    //first triangle

    /*if(PointInTriangle(vec2(px,py),vec2(0,0),p1,p4)){
        px = px + p3.x;
    }*/
    if (PointInTriangle(vec2(px+1.0,py),vec2(0,0),p1,p4)){
        px = px -1.5 + p3.x;
    }
    else if (PointInTriangle(vec2(px-1.0,py),vec2(0,0),p1,p4)){
        px = px -1.5 + p3.x;
    }
    return vec2(px,py); 
}

void main( void )
{
    updateCornerPoints();

	vec4 color = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
	vec2 pos = gl_TexCoord[0].st;

    pos = rotateAt(pos,vec2(width/2,height/2),angle);
    if(cell_structure == SQUARE){
        pos = do_square(pos);
    }
    if(cell_structure == HEXAGONAL){
        pos = do_hexagonal(pos);
    }
    
    
    vec4 c = texture2DRect( u_tex_unit0, pos);
    gl_FragColor = c;
}