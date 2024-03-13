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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif 

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World sss", "fonts/Marker Felt.ttf", 24);
	//if (label == nullptr)
	//{
	//    problemLoading("'fonts/Marker Felt.ttf'");
	//}
	//else
	//{
	//    // position the label on the center of the screen
	//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
	//                            origin.y + visibleSize.height - label->getContentSize().height));

	//    // add the label as a child to this layer
	//    this->addChild(label, 1);
	//}

	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//    problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//    // position the sprite on the center of the screen
	//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//    // add the sprite as a child to this layer
	//    this->addChild(sprite, 0);
	//}

	MenuItemFont::setFontSize(14);

	auto menu_item_Login = MenuItemFont::create("Login", CC_CALLBACK_1(HelloWorld::Login, this));
	auto menu_item_GetMeInfo = MenuItemFont::create("GetMeInfo", CC_CALLBACK_1(HelloWorld::GetMeInfo, this));
	auto menu_item_switchAccount = MenuItemFont::create("SwitchAccount", CC_CALLBACK_1(HelloWorld::SwitchAccount, this));
	auto menu_item_rechargeSP = MenuItemFont::create("RechargeSP", CC_CALLBACK_1(HelloWorld::RechargeSP, this));
	auto menu_item_consumeSP = MenuItemFont::create("ConsumeSP", CC_CALLBACK_1(HelloWorld::ConsumeSP, this));


	menu_item_Login->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 6) * 5));
	menu_item_GetMeInfo->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 6) * 4));
	menu_item_switchAccount->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 6) * 3));
	menu_item_rechargeSP->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 6) * 2));
	menu_item_consumeSP->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 6) * 1));

	auto* toolMenu = Menu::create(menu_item_Login, menu_item_GetMeInfo, menu_item_switchAccount, menu_item_rechargeSP, menu_item_consumeSP, NULL);
	toolMenu->setPosition(Point(0, 0));

	this->addChild(toolMenu);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}




void HelloWorld::Login(cocos2d::Ref* pSender) {
	log("Login");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getConnect17dameInstance", "()Lorg/cocos2dx/cpp/AppActivity;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openLoginWebview", "(Ljava/lang/String;)V");

		if (isHave) {
			jstring state = minfo.env->NewStringUTF("App-side-State");
			minfo.env->CallVoidMethod(jobj, minfo.methodID, state);
		}
	}
#else
	// CCDirector::sharedDirector()->end();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
#endif 
}

void HelloWorld::GetMeInfo(cocos2d::Ref* pSender) {
	log("GetMeInfo");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getConnect17dameInstance", "()Lorg/cocos2dx/cpp/AppActivity;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "GetMeInfo", "()V");

		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
#else
	// CCDirector::sharedDirector()->end();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
#endif 
}

void HelloWorld::SwitchAccount(cocos2d::Ref* pSender) {
	log("SwitchAccount");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getConnect17dameInstance", "()Lorg/cocos2dx/cpp/AppActivity;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openSwitchAccountWebview", "()V"); 
		if (isHave) {
			minfo.env->CallVoidMethod(jobj, minfo.methodID);
		}
	}
#else
	// CCDirector::sharedDirector()->end();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
#endif 
}
void HelloWorld::RechargeSP(cocos2d::Ref* pSender) {
	log("RechargeSP");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getConnect17dameInstance", "()Lorg/cocos2dx/cpp/AppActivity;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openRechargeSPWebview", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (isHave) {
			jstring currencyCode = minfo.env->NewStringUTF("2"); // TWD
			jstring notifyUrl = minfo.env->NewStringUTF(""); // notifyUrl 
			jstring state = minfo.env->NewStringUTF("Custom state");

			minfo.env->CallVoidMethod(jobj, minfo.methodID, currencyCode, notifyUrl, state);
		}
	}
#else
	// CCDirector::sharedDirector()->end();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
#endif 
}
void HelloWorld::ConsumeSP(cocos2d::Ref* pSender) {
	log("ConsumeSP");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "getConnect17dameInstance", "()Lorg/cocos2dx/cpp/AppActivity;");
	jobject jobj;
	if (isHave) {
		jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		isHave = JniHelper::getMethodInfo(minfo, "org/cocos2dx/cpp/AppActivity", "openConsumeSPWebview", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

		if (isHave) {

			jint consume_spCoin = 10;
			jstring orderNo = minfo.env->NewStringUTF("");
			jstring productName = minfo.env->NewStringUTF("productName");
			jstring GameName = minfo.env->NewStringUTF("GameName");
			jstring notifyUrl = minfo.env->NewStringUTF("");
			jstring state = minfo.env->NewStringUTF("state");
			jstring requestNumber = minfo.env->NewStringUTF("91f039df-eb20-4682-a56c-4ccb7c37db16");

			minfo.env->CallVoidMethod(jobj, minfo.methodID, consume_spCoin, orderNo, GameName, productName, notifyUrl, state, requestNumber);
		}
	}
#else
	// CCDirector::sharedDirector()->end();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif  
#endif 
}