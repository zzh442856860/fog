#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TiledFourCell.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayerColor
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);

    //add code
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );

    virtual void registerWithTouchDispatcher( void );

    CCPoint getMapTiledPos( CCTMXTiledMap* map, CCPoint pos);

    void changeCloudTiled4( CCTMXLayer* layer, CCPoint pos );

    void setGidByTotalNum( CCTMXLayer* layer, CCPoint pos, int iTotalNum );

    TiledFourCell* getCellByTiledPos( CCPoint pos );

    void changeCloudTiled8( CCTMXLayer* layer, CCPoint pos );

    void changeCloudTiled1( CCTMXLayer* layer, CCPoint pos );

    void changeCloudTiled2( CCTMXLayer* layer, CCPoint pos );
private:
    CCTMXTiledMap* cloudMap;

    CCDictionary* tiledCellsDict; // 瓦片坐标和瓦片顶点对象 键值对

    CCArray* gidsArray; // 瓦片图片gid与瓦片顶点数值总和对应

};

#endif // __HELLOWORLD_SCENE_H__
