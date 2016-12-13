#version 120
#extension GL_ARB_texture_rectangle : enable

#define PI 3.141592653589793

#define P4 9
#define P4M 10
#define P4G 11
#define P3 12
#define P3M1 13
#define P31M 14
#define P6 15
#define P6mm 16



uniform sampler2DRect 	u_tex_unit0;
uniform float 			width,height;
uniform int 			wallpaper_group;
						/*
						0 = P1,
					    1 = P2,
					    2 = PM,
					    3 = PG,
					    4 = CM,
					    5 = PMM,
					    6 = PMG,
					    7 = PGG,
					    8 = CMM
						*/
uniform int 			cell_structure;
						/*
						0 = RECTANGLE,
    					1 = SQUARE,
    					2 = RHOMBIC,
    					3 = HEXAGONAL,
    					4 = OBLIQUE
    					*/


vec2 p1,p2,p3,p4;
vec2 base1,base2,base3,base4,mid;
vec2 p1p2, p2p3, p3p4, p1p4;

/*****************
* Transformation *
******************/
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


/************************
 * Position calculation *
 ************************/
void getBorders(){
	if (cell_structure == 1){
			float lengthCell = min(width, height);
            p1 = vec2((width-lengthCell)/2, (height-lengthCell)/2);
            p2 = vec2((width-lengthCell)/2 + lengthCell, (height-lengthCell)/2);
            p3 = vec2((width-lengthCell)/2 + lengthCell, (height-lengthCell)/2 + lengthCell);
            p4 = vec2((width-lengthCell)/2, (height-lengthCell)/2 + lengthCell);
	}
	else if (cell_structure == 3){
		float hmax = width*sqrt(3)/3;
		float wmax = width;

		if (hmax>height) {
			hmax = height;
			wmax = hmax*3/sqrt(3);
		}

		p1 = vec2(wmax*1/3,0);
		p2 = vec2(wmax,0);
		p3 = vec2(wmax*2/3,hmax);
		p4 = vec2(0,hmax);
	}
	
}
bool PointInTriangle(vec2 p, vec2 p0, vec2 p1, vec2 p2)
{
    float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
    float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

    if ((s < -0) != (t < 0))
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

bool isInTile(vec2 p)
{
	//pt resolves edge jitter
	vec2 pt = vec2(p.x-0.1,p.y-0.1);
	if(PointInTriangle(p,p1,p2,p4) || PointInTriangle(p,p2,p3,p4)
		||PointInTriangle(pt,p1,p2,p4) || PointInTriangle(pt,p2,p3,p4)){
		return true;
	}
	return false;
}

//type 0=P4, 1=P4M, 2=P4G
int getTileSquare(vec2 pos,int type){
	//ornament base
	mid = p1 + (p3-p1)/2;
	p1p2 = p1 + (p2-p1)/2;
	p2p3 = p2 + (p3-p2)/2;
	p3p4 = p3 + (p4-p3)/2;
	p1p4 = p1 + (p4-p1)/2;

	int t1,t2;

	if(PointInTriangle(pos,p1,p1p2,mid)){
		t1 = 0;
		if(PointInTriangle(pos,p1,p1p2,p1 + (mid-p1)/2)){
			t2 = 0;
		}
		else{
			t2 = 1;
		}
	}
	else if(PointInTriangle(pos,p1,mid,p1p4)){
		t1 = 0;
		if(PointInTriangle(pos,p1,p1p4,p1 + (mid-p1)/2)){
			t2 = 2;
		}
		else{
			t2 = 3;
		}
	}
	else if(PointInTriangle(pos,p1p2,p2,p2p3)){
		t1 = 1;
		if(PointInTriangle(pos,p1p2,p2,p2 + (mid-p2)/2)){
			t2 = 0;
		}
		else{
			t2 = 1;
		}
	}
	else if(PointInTriangle(pos,p1p2,p2p3,mid)){
		t1 = 1;
		if(PointInTriangle(pos,p1p2,mid,p2 + (mid-p2)/2)){
			t2 = 2;
		}
		else{
			t2 = 3;
		}
	}
	else if(PointInTriangle(pos,mid,p2p3,p3)){
		t1 = 2;
		if(PointInTriangle(pos,mid,p2p3,p2p3 + (p3p4-p2p3)/2)){
			t2 = 0;
		}
		else{
			t2 = 1;
		}
	}
	else if(PointInTriangle(pos,mid,p3,p3p4)){
		t1 = 2;
		if(PointInTriangle(pos,mid,p3p4,p3p4 + (p2p3-p3p4)/2)){
			t2 = 2;
		}
		else{
			t2 = 3;
		}
	}
	else if(PointInTriangle(pos,p1p4,mid,p3p4)){
		t1 = 3;
		if(PointInTriangle(pos,mid,p1p4,p1p4 + (p3p4-p1p4)/2)){
			t2 = 0;
		}
		else{
			t2 = 1;
		}
	}
	else{
		t1 = 3;
		if(PointInTriangle(pos,p4,p3p4,p1p4 + (p3p4-p1p4)/2)){
			t2 = 2;
		}
		else{
			t2 = 3;
		}
	}

	int t = t1*4 + t2;
	//return t1;

	int lut[16];
	if(type == 0){
				   // 00 01 02 03 10 11 12 13 20 21 22 23 30 31 32 33 
		lut = int[16]( 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3);
	}else if(type == 1){
				   // 00 01 02 03  10  11  12  13  20  21  22  23  30  31  32  33 
		lut = int[16]( 0, 0, 1, 1, 10, 11, 10, 11, 20, 20, 21, 21, 30, 31, 31, 30);
	}
	else if(type == 2){
				   // 00 01 02 03  10  11  12  13  20  21  22  23  30  31  32  33 
		lut = int[16]( 1, 0, 1, 0, 11, 11, 10, 10, 21, 20, 21, 20, 31, 31, 30, 30);
	}
	return lut[t];
}

int getTileTriangle(vec2 pos,int type){
	//ornament base
	base1 = p1;
		vec2 p1p2 = p1 + (p2-p1)/2;
    	base2 = p1p2 + (p3-p1p2)/3;
    	base3 = p3;
   		vec2 p1p4 = p1 + (p4-p1)/2;
    	base4 = p1p4 + (p3-p1p4)/3;

	int t1,t2,t3;

	if(PointInTriangle(pos,p1,p3,p4)){
		t1 = 0;
		if(PointInTriangle(pos,p1,p3,base4)){
			t2 = 0;
			if (PointInTriangle(pos,p1,p1 + (p3-p1)/2,base4)) t3 = 0;
			else t3 = 1;
		}else if(PointInTriangle(pos,p4,p3,base4)){
			t2 = 1;
			if (PointInTriangle(pos,p3,p4 + (p3-p4)/2,base4)) t3 = 0;
			else t3 = 1;
		}
		else{
			t2 = 2;
			if (PointInTriangle(pos,p4,p4 + (p1-p4)/2,base4)) t3 = 0;
			else t3 = 1;
		}
	}else{
		t1 = 1;
		if(PointInTriangle(pos,p1,p3,base2)){
			t2 = 0;
			if (PointInTriangle(pos,p1,p1 + (p3-p1)/2,base2)) t3 = 0;
			else t3 = 1;
		}else if(PointInTriangle(pos,p1,p2,base2)){
			t2 = 1;
			if (PointInTriangle(pos,p2,p1 + (p2-p1)/2,base2)) t3 = 0;
			else t3 = 1;
		}
		else{
			t2 = 2;
			if (PointInTriangle(pos,p3,p3 + (p2-p3)/2,base2)) t3 = 0;
			else t3 = 1;
		}
	}
	int t = t1*6 + t2*2 + t3;

	int lut[12];
	if(type == 0){
				   // 000 001 010 011 020 021 100 101 110 111 120 121 
		lut = int[12]( 0,  0,  3,  3,  4,  4,  0,  0,  1,  1,  2,  2);
	}else if(type == 1){
				   // 000 001 010 011 020 021 100 101 110 111 120 121 
		lut = int[12]( 0,  1, 31, 30, 40, 41,  0,  1, 11, 10,  20, 21);
	}else if(type == 2 || type == 3){
				   // 000 001 010 011 020 021 100 101 110 111 120 121 
		lut = int[12]( 0,  0,  4,  4,  5,  5,  1,  1,  2,  2,  3,  3);
	}else if(type == 4){
				   // 000 001 010 011 020 021 100 101 110 111 120 121 
		lut = int[12]( 0,  1,  40,  41,  50,  51,  10,  11,  20,  21,  30,  31);
	}

	return lut[t];
}
/*************************************
 * WALLPAPER RENDERING  P4 Groups*
 ************************************/
void do_p4(vec2 pos)
{
	int s = getTileSquare(pos, 0);



	if (s == 0){
		gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
	}
	else if (s == 1){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,-PI*0.5) );
	}
	else if (s == 2){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
	}
	else {
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5) );
	}
}

void do_p4m(vec2 pos)
{
	int s = getTileSquare(pos, 1);

	if (s == 0){
		gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
	}
	else if (s == 1){
		gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
	}
	else if (s == 10){
		gl_FragColor = texture2DRect( u_tex_unit0, reflectAt(pos,p1p2,mid-p1p2) );
	}
	else if (s == 11){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*1.5) );
	}
	else if (s == 20){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(reflectAt(pos,p1p2,mid-p1p2),mid,PI*0.5));
	}
	else if (s == 21){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
	}
	else if (s == 30){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5));
	}
	else if (s == 31){
		gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1p4,mid - p1p4) );
	}
}

void do_p4g(vec2 pos)
{
	int s = getTileSquare(pos, 2);

	if (s == 0){
		gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
	}
	else if (s == 1){
		gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1p2,p1p4-p1p2) );
	}
	else if (s == 10){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(pos,mid,PI*1.5) );
	}
	else if (s == 11){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt(reflectAt(pos,p1p2,p2p3-p1p2),mid,PI*1.5) );
	}
	else if (s == 20){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (reflectAt (pos,p2p3,p3p4-p2p3),mid,PI) );
	}
	else if (s == 21){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI) );
	}
	else if (s == 30){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (reflectAt (pos,p1p4,p3p4-p1p4),mid,PI*0.5));
	}
	else if (s == 31){
		gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,mid,PI*0.5)  );
	}
}

/*************************************
 * WALLPAPER RENDERING  P3, P6 Groups*
 ************************************/
void do_p3(vec2 pos)
{
	int p = getTileTriangle(pos,0);
	if (p==0){ 
			gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
		}
		else if (p==1) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,-2*PI/3) );
		}
		else if (p==2) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,2*PI/3) );
		}
		else if (p==3) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
		}
		else if (p==4) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
		}
}

void do_p3m1(vec2 pos)
{
	int p = getTileTriangle(pos,1);
		if (p==0){ 
			gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
		}
		else if (p==1){ 
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,base4,base2-base4) );
		}
		else if (p==10) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,-2*PI/3),base4,base2-base4) );
		}
		else if (p==11) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,-2*PI/3) );
		}
		else if (p==20) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base2,2*PI/3) );
		}
		else if (p==21) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,2*PI/3),base4,base2-base4) );
		}
		else if (p==30) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4,-2*PI/3),base4,base2-base4) );
		}
		else if (p==31) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
		}
		else if (p==40) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
		}
		else if (p==41) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4,2*PI/3),base4,base2-base4) );
		}
}

void do_p31m(vec2 pos)
{
	int p = getTileTriangle(pos,2);
	if (p==0){ 
			gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
		}
		else if (p==1) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
		}
		else if (p==2) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,-2*PI/3),p1,p3-p1) );
		}
		else if (p==3) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base2,2*PI/3),p1,p3-p1) );
		}
		else if (p==4) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,-2*PI/3) );
		}
		else if (p==5) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4,2*PI/3) );
		}
}

void do_p6(vec2 pos)
{
	int p = getTileTriangle(pos,3);
	if (p==0){ 
			gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
		}
		else if (p==1) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,p1 + (p3-p1)/2, PI) );
		}
		else if (p==2) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3) );
		}
		else if (p==3) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3) );
		}
		else if (p==4) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, 4*PI/3) );
		}
		else if (p==5) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, PI-PI/3) );
		}
}

void do_p6mm(vec2 pos)
{
	int p = getTileTriangle(pos,4);
	if (p==0){ 
			gl_FragColor = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
		}
		else if (p==1) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p4,p2-p4) );
		}
		else if (p==10) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (pos,p1,p3-p1) );
		}
		else if (p==11) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,p1 + (p3-p1)/2, PI) );
		}
		else if (p==20) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3),p4,p2-p4) );
		}
		else if (p==21) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, 4*PI/3) );
		}
		else if (p==30) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3),p4,p2-p4) );
		}
		else if (p==31) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (rotateAt (pos,p1 + (p3-p1)/2, PI),base4, PI-PI/3) );
		}
		else if (p==40) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, 4*PI/3) );
		}
		else if (p==41) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4, 4*PI/3),p4,p2-p4) );
		}
		else if (p==50) {
			gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,base4, PI-PI/3) );
		}
		else if (p==51) {
			gl_FragColor = texture2DRect( u_tex_unit0, reflectAt (rotateAt (pos,base4, PI-PI/3),p4,p2-p4) );
		}
}

void main( void )
{
	getBorders();

	vec4 color = texture2DRect( u_tex_unit0, gl_TexCoord[0].st );
	vec2 pos = gl_TexCoord[0].st;
	
	 

	//gl_FragColor = texture2DRect( u_tex_unit0, rotateAt (pos,vec2(width/2,height/2),cos(u_time) ));
	if(isInTile(pos)){
		if (wallpaper_group == P4) do_p4(pos);
		else if (wallpaper_group == P4M) do_p4m(pos);
		else if (wallpaper_group == P4G) do_p4g(pos);
		else if (wallpaper_group == P3) do_p3(pos);
		else if (wallpaper_group == P3M1) do_p3m1(pos);
		else if (wallpaper_group == P31M) do_p31m(pos);
		else if (wallpaper_group == P6) do_p6(pos);
		else if (wallpaper_group == P6mm) do_p6mm(pos);
		
	}else{
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
	}


}