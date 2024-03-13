
/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ConnectToolCocosScene.h" 

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include <jni.h>
//#include "platform/android/jni/JniHelper.h"
//#endif 


USING_NS_CC;

Scene* ConnectToolCocos::createScene()
{
	auto scene = Scene::create();
	auto layer = ConnectToolCocos::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool ConnectToolCocos::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	toolSprite = Sprite::create("CloseNormal.png");
	toolSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
	this->addChild(toolSprite);

	auto menu_item_Login = MenuItemFont::create("Login", CC_CALLBACK_1(ConnectToolCocos::Login, this));
	auto menu_item_switchAccount = MenuItemFont::create("SwitchAccount", CC_CALLBACK_1(ConnectToolCocos::SwitchAccount, this));
	auto menu_item_rechargeSP = MenuItemFont::create("RechargeSP", CC_CALLBACK_1(ConnectToolCocos::RechargeSP, this));
	auto menu_item_consumeSP = MenuItemFont::create("ConsumeSP", CC_CALLBACK_1(ConnectToolCocos::ConsumeSP, this));

	menu_item_Login->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 5) * 4));
	menu_item_switchAccount->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 5) * 3));
	menu_item_rechargeSP->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 5) * 2));
	menu_item_consumeSP->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 5) * 1));

	auto* menu = Menu::create(menu_item_Login, menu_item_switchAccount, menu_item_rechargeSP, menu_item_consumeSP, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);




	return true;
}

void ConnectToolCocos::Login(cocos2d::Ref* pSender) {
	log("Login");
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo minfo;
//	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/jacky/test/Test", "getInstance", "()Lcom/jacky/test/Test;");
//	jobject jobj;
//	if (isHave) {
//		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//		isHave = JniHelper::getStaticMethodInfo(minfo, "com/jacky/test/Test", "openWebview", "()V");
//
//		if (isHave) {
//			minfo.env->CallVoidMethod(jobj, minfo.methodID);
//		}
//	}
//
//#else
//	// CCDirector::sharedDirector()->end();
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	exit(0);
//#endif  
//#endif 
}
void ConnectToolCocos::SwitchAccount(cocos2d::Ref* pSender) {
	log("SwitchAccount");
}
void ConnectToolCocos::RechargeSP(cocos2d::Ref* pSender) {
	log("RechargeSP");
}
void ConnectToolCocos::ConsumeSP(cocos2d::Ref* pSender) {
	log("ConsumeSP");
}

