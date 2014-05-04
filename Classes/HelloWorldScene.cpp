#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCLayerColor::initWithColor(ccc4(255, 255, 255, 255));
    
    cloudMap = CCTMXTiledMap::create("blackCloud.tmx");
    
    this->addChild(cloudMap);
    
    this->setTouchEnabled(true);
    
    
    gidsArray = CCArray::createWithCapacity(16);

    tiledCellsDict = CCDictionary::create();
    
    gidsArray->retain();

    tiledCellsDict->retain();
    /* 瓦片地图使用4X4的图片，每张小图片对应的数值如下：
     
     0 4 8 12
     
     1 5 9 13
     
     2 6 10 14
     
     3 7 11 15
     
     以上数值为瓦片格子的数据值。
     
     瓦片图素从1开始计数，如下：
     
     1 2 3 4
     
     5 6 7 8
     
     9 10 11 12
     
     13 14 15 16
     
     比如数据值4，对应的瓦片图素是2；数据值10，对应的瓦片图素是11。
     
     */
    
    /* 以数据值为索引，可以取得瓦片图素 */
    
    gidsArray->addObject(CCInteger::create(1));//顶点总和0，对应图素ID为1
    
    gidsArray->addObject(CCInteger::create(5));// 顶点总和1，对应图素ID为5
    
    gidsArray->addObject(CCInteger::create(9));// 顶点总和2，对应图素ID为9
    
    gidsArray->addObject(CCInteger::create(13));// 顶点总和3，对应图素ID为13
    
    gidsArray->addObject(CCInteger::create(2));// 顶点总和4，对应图素ID为2
    
    gidsArray->addObject(CCInteger::create(6));// 顶点总和5，对应图素ID为6
    
    gidsArray->addObject(CCInteger::create(10));
    
    gidsArray->addObject(CCInteger::create(14));
    
    gidsArray->addObject(CCInteger::create(3));
    
    gidsArray->addObject(CCInteger::create(7));
    
    gidsArray->addObject(CCInteger::create(11));
    
    gidsArray->addObject(CCInteger::create(15));
    
    gidsArray->addObject(CCInteger::create(4));
    
    gidsArray->addObject(CCInteger::create(8));
    
    gidsArray->addObject(CCInteger::create(12));
    
    gidsArray->addObject(CCInteger::create(16));
    
    return true;
}

//void HelloWorld::menuCloseCallback(CCObject* pSender)
//{
//    CCDirector::sharedDirector()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//}

bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLog("helloworld");
    CCPoint tiledMapPos = getMapTiledPos(
                                         
                                         cloudMap,
                                         
                                         CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView()));
    
    CCLOG("TiledMapPos x = %f, y = %f", tiledMapPos.x, tiledMapPos.y);

    
    CCTMXLayer* cloudLayer = cloudMap->layerNamed("cloudLayer");
    
    /* 设置当前瓦片的数据值，以及设置旁白瓦片的数据值 */

    changeCloudTiled4(cloudLayer, tiledMapPos);
    
    changeCloudTiled8(cloudLayer, ccp(tiledMapPos.x + 1, tiledMapPos.y));
    
    changeCloudTiled1(cloudLayer, ccp(tiledMapPos.x, tiledMapPos.y + 1));

    changeCloudTiled2(cloudLayer, ccp(tiledMapPos.x + 1, tiledMapPos.y + 1));

    return true;
}

void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

CCPoint HelloWorld::getMapTiledPos(CCTMXTiledMap *map, CCPoint pos)
{
    CCSize mapSize = map->getMapSize();
    
    CCSize tiledSize = map->getTileSize();
    
    int iMapHeight = mapSize.height * tiledSize.height;
    
    /* pos为笛卡尔坐标系的坐标，所以y轴需要修正 */
    
    int x = pos.x / tiledSize.width;
    
    int y = (iMapHeight - pos.y) / tiledSize.height;
    
    return CCPointMake(x, y);
}


void HelloWorld::changeCloudTiled4(CCTMXLayer *layer,CCPoint pos)
{
    TiledFourCell* cell = getCellByTiledPos(pos);
    
    /* 数值4，在瓦片右下角 */
    cell->setiRightBottom(4);
    
    /* 根据瓦片4个顶点之和设置地图瓦片的图片 */
    setGidByTotalNum(layer, pos, cell->getiTotalNum());


}

void HelloWorld::changeCloudTiled8(CCTMXLayer *layer, CCPoint pos)
{
    TiledFourCell* cell = getCellByTiledPos(pos);
    cell->setiLeftBottom(8);
    setGidByTotalNum(layer, pos, cell->getiTotalNum());
}

void HelloWorld::changeCloudTiled1(CCTMXLayer *layer, CCPoint pos)
{
    TiledFourCell* cell = getCellByTiledPos(pos);
    cell->setiRightTop(1);
    setGidByTotalNum(layer, pos, cell->getiTotalNum());
}

void HelloWorld::changeCloudTiled2(CCTMXLayer *layer, CCPoint pos)
{
    TiledFourCell* cell = getCellByTiledPos(pos);
    cell->setiLeftTop(2);
    setGidByTotalNum(layer, pos, cell->getiTotalNum());
}

void HelloWorld::setGidByTotalNum( CCTMXLayer* layer, CCPoint pos, int iTotalNum )
{
    
    CCSize mapSize = cloudMap->getMapSize();
    
    /* 避免超出范围 */
    
    if(pos.x < 0 || pos. y < 0
       
       || pos.x >= mapSize.width || pos.y >= mapSize.height) {
        
        return;
        
    }
    
    /* iTotalNum是瓦片的4个顶点数据值的总和，通过这个值获得对应的瓦片图素 */
    
    CCInteger* gidInt = (CCInteger*)gidsArray->objectAtIndex(iTotalNum);

    /* 用新的瓦片图素替换pos坐标上的瓦片图素 */
    
    layer->setTileGID(gidInt->getValue(), pos);

}

TiledFourCell* HelloWorld::getCellByTiledPos( CCPoint pos )
{
    CCSize mapSize = cloudMap->getMapSize();
    
    /* 瓦片坐标原本是二维坐标，转换为一维数值 */
    
    int index = mapSize.width * pos.x + pos.y;
    
    /* 取得瓦片的顶点数据对象 */
    
    const char* keyCh = CCString::createWithFormat("%d", index)->getCString();
    
    CCObject* obj = tiledCellsDict->objectForKey(keyCh);
    
    TiledFourCell* cell = NULL;
    
    if(obj == NULL) {
        
        /* 如果该瓦片没有顶点数据对象，则创建一个，顶点数据值默认都为0 */
        
        cell = TiledFourCell::create();
        
        tiledCellsDict->setObject(cell, keyCh);
        
    }
    
    else {
        
        cell = (TiledFourCell*)obj;
        
    }
    
    return cell;

}

