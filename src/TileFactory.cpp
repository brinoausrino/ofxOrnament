/*
 *  TileFactory.cpp
 *  textureExample
 *
 *  Created by Brian Eschrich on 01.10.15
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "TileFactory.h"
#include "Tile_P1.h"
#include "Tile_P2.h"
#include "Tile_PM.h"
#include "Tile_PG.h"
#include "Tile_CM.h"
#include "Tile_PMM.h"
#include "Tile_PMG.h"
#include "Tile_PGG.h"
#include "Tile_CMM.h"
#include "Tile_P4.h"
#include "Tile_P4M.h"
#include "Tile_P4G.h"
#include "Tile_P3.h"
#include "Tile_P3M1.h"
#include "Tile_P31M.h"
#include "Tile_P6.h"
#include "Tile_P6M.h"

std::unique_ptr<Tile>  TileFactory::createTile(WALLPAPER_GROUP tileType) {
    switch (tileType) {
        case WPG_P1:
            return std::unique_ptr<Tile_P1>(new Tile_P1());
            break;
        case WPG_P2:
            return std::unique_ptr<Tile_P2>(new Tile_P2());
            break;
        case WPG_PM:
            return std::unique_ptr<Tile_PM>(new Tile_PM());
            break;
        case WPG_PG:
            return std::unique_ptr<Tile_PG>(new Tile_PG());
            break;
        case WPG_CM:
            return std::unique_ptr<Tile_CM>(new Tile_CM());
            break;
        case WPG_PMM:
            return std::unique_ptr<Tile_PMM>(new Tile_PMM());
            break;
        case WPG_PMG:
            return std::unique_ptr<Tile_PMG>(new Tile_PMG());
            break;
        case WPG_PGG:
            return std::unique_ptr<Tile_PGG>(new Tile_PGG());
            break;
        case WPG_CMM:
            return std::unique_ptr<Tile_CMM>(new Tile_CMM());
            break;
        case WPG_P4:
            return std::unique_ptr<Tile_P4>(new Tile_P4());
            break;
        case WPG_P4M:
            return std::unique_ptr<Tile_P4M>(new Tile_P4M());
            break;
        case WPG_P4G:
            return std::unique_ptr<Tile_P4G>(new Tile_P4G());
            break;
        case WPG_P3:
            return std::unique_ptr<Tile_P3>(new Tile_P3());
            break;
        case WPG_P3M1:
            return std::unique_ptr<Tile_P3M1>(new Tile_P3M1());
            break;
        case WPG_P31M:
            return std::unique_ptr<Tile_P31M>(new Tile_P31M());
            break;
        case WPG_P6:
            return std::unique_ptr<Tile_P6>(new Tile_P6());
            break;
        case WPG_P6M:
            return std::unique_ptr<Tile_P6M>(new Tile_P6M());
            break;
        default:
            break;
    }
    
}


