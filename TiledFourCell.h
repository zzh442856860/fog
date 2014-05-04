//
//  TiledFourCell.h
//  Fog
//
//  Created by IDEA-MAC03 on 13-8-29.
//
//

#ifndef __Fog__TiledFourCell__
#define __Fog__TiledFourCell__

#include "cocos2d.h"
using namespace cocos2d;

class TiledFourCell : public CCNode
{
public:
    CREATE_FUNC(TiledFourCell);
    
    virtual bool init();
    
    void setiLeftTop(int _iLeftTop);
    
    int getiLeftTop();
    
    void setiLeftBottom(int _iLeftBottom);
    
    int getiLeftBottom();
    
    void setiRightTop(int _iRightTop);
    
    int getiRightTop();
    
    void setiRightBottom(int _iRightBottom);
    
    int getiRightBottom();
    
    /* 获取顶点值的总和 */
    int getiTotalNum();

private:
    
    int iLeftTop; // 左上角

    int iLeftBottom;// 左下角

    int iRightTop; // 右上角

    int iRightBottom; // 右下角

};


#endif /* defined(__Fog__TiledFourCell__) */
