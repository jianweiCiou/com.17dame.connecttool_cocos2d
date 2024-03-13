/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
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
package org.cocos2dx.cpp;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Build;
import android.util.Log;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.r17dame.connecttool.ConnectTool;
import com.r17dame.connecttool.ConnectToolBroadcastReceiver;


import java.security.NoSuchAlgorithmException;
import java.util.UUID;

public class AppActivity extends Cocos2dxActivity {

    // region ****************** for 17dame tool ********************************
    // 取得網頁事件回應
    private ConnectToolBroadcastReceiver connectReceiver;
    // Cocos2d 呼應實體
    private static AppActivity connect17dameActivity;
    // 17 dame 工具
    ConnectTool _connectTool;
    private final static String TAG = "ConnectTool test";
    IntentFilter itFilter;
    // endregion

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.setEnableVirtualButton(false);
        super.onCreate(savedInstanceState);
        // Workaround in https://stackoverflow.com/questions/16283079/re-launch-of-activity-on-home-button-but-only-the-first-time/16447508
        if (!isTaskRoot()) {
            // Android launched another instance of the root activity into an existing task
            //  so just quietly finish and go away, dropping the user back into the activity
            //  at the top of the stack (ie: the last state of this task)
            // Don't need to finish it again since it's finished in super.onCreate .
            return;
        }
        // Make sure we're running on Pie or higher to change cutout mode
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            // Enable rendering into the cutout area
            WindowManager.LayoutParams lp = getWindow().getAttributes();
            lp.layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
            getWindow().setAttributes(lp);
        }
        // DO OTHER INITIALIZATION BELOW

        // region ****************** 17dame tool ********************************
        // init callback
        connect17dameActivity = this;
        _connectTool = new ConnectTool(
                this,
                "",
                "",
                "",
                "",
                "");

        _connectTool.setPlatformVersion(ConnectTool.PLATFORM_VERSION.cocos2dVS);
        _connectTool.setToolVersion(ConnectTool.TOOL_VERSION.testVS);
        // _connectTool.setToolVersion(ConnectTool.TOOL_VERSION.releaseVS);

        // 設定 17dame 網頁
        _connectTool.connectCocos_webLayout = new FrameLayout(this);
        addContentView(_connectTool.connectCocos_webLayout, _connectTool.getFrameLayoutParams());

        // Init 17dame registerReceiver
        itFilter = new IntentFilter();
        itFilter.addAction("com.r17dame.CONNECT_ACTION");
        connectReceiver = new ConnectToolBroadcastReceiver();
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.UPSIDE_DOWN_CAKE) {
            // 修正 Android 14+ 的廣播註冊
            this.registerReceiver(connectReceiver, itFilter, RECEIVER_EXPORTED);
        } else {
            registerReceiver(connectReceiver, itFilter);
        }

        connectReceiver.registerCallback(new ConnectToolBroadcastReceiver.ConnectToolReceiverCallback() {
            @Override
            public void connectToolPageBack(Intent intent, String accountBackType) {
                String backType = intent.getStringExtra("accountBackType");
                Log.v(TAG, "connectToolPageBack : " + backType);
                // Open by Account Page (Register, Login) :
                if (backType.equals("Register")) {
                    /*
                     * App-side add functions.
                     */
                    String state = "App-side-State";
                    _connectTool.AccountPageEvent(state, backType);
                }
                // Login
                if (backType.equals("Login")) {
                    /*
                     * App-side add functions.
                     */
                    String state = "App-side-State";
                    _connectTool.AccountPageEvent(state, backType);
                }

                // Complete purchase of SP Coin
                if (backType.equals("CompletePurchase")) {
                    _connectTool.appLinkDataCallBack_CompletePurchase(intent, value -> {
                        Log.v(TAG, "appLinkData CompletePurchase callback : " + value);
                        //Toast.makeText(getApplicationContext(), "Purchase tradeNo : " + value.data.tradeNo + "/ spCoin : " + value.data.spCoin, Toast.LENGTH_SHORT).show();
                        /*
                         * App-side add functions.
                         */
                        return value;
                    });
                }

                // Complete consumption of SP Coin
                if (backType.equals("CompleteConsumeSP")) {
                    UUID queryConsumeSP_requestNumber = UUID.randomUUID(); // App-side-RequestNumber(UUID), default random
                    // consume_transactionId
                    _connectTool.appLinkDataCallBack_CompleteConsumeSP(intent, queryConsumeSP_requestNumber, value -> {
                        /*
                         * App-side add functions.
                         */
                        Log.v(TAG, "appLinkData CompleteConsumeSP callback : " + value.data.orderStatus);
                        //Toast.makeText(getApplicationContext(), "consumption orderNo : " + value.data.orderNo + "/ spCoin : " + value.data.spCoin + "/ rebate : " + value.data.rebate, Toast.LENGTH_SHORT).show();
                    });
                }

                // get Access token
                if (backType.equals("Authorize")) {
                    UUID GetMe_RequestNumber = UUID.randomUUID(); // App-side-RequestNumber(UUID), default random
                    String state = "App-side-State";
                    _connectTool.appLinkDataCallBack_OpenAuthorize(intent, state, GetMe_RequestNumber, value -> {
                        Log.v(TAG, "User email : " + value.meInfo.data.email);
                        /*
                         * App-side add functions.
                         */
                        // Toast.makeText(getApplicationContext(), value.meInfo.data.email, Toast.LENGTH_SHORT).show();
                    });
                }
            }
        });
        // endregion
    }

    // region ****************** 17dame tool open Webview ********************************
    public static AppActivity getConnect17dameInstance() {
        return connect17dameActivity;
    }

    private void openLoginWebview(String state) {
        _connectTool.getAuthorizeURL(state);
        openWebview();
    }

    private void GetMeInfo() {
        UUID GetMe_RequestNumber = UUID.randomUUID(); // App-side-RequestNumber(UUID), default random
        try {
            _connectTool.GetMe_Coroutine(GetMe_RequestNumber, value -> {
                /*
                 * App-side add functions.
                 */
                Log.v(TAG, "GetMe_RequestNumber : " + value.requestNumber);
                Log.v(TAG, "MeInfo email : " + value.data.email);
                Log.v(TAG, "MeInfo spCoin : " + value.data.spCoin);
                Log.v(TAG, "MeInfo userId : " + value.data.userId);
                Toast.makeText(getApplicationContext(), value.data.email, Toast.LENGTH_SHORT).show();
            });
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }



    private void openSwitchAccountWebview() {
        _connectTool.getLoginURL();
        openWebview();
    }

    private void openRechargeSPWebview(String currencyCode, String notifyUrl, String state) {
        _connectTool.getRechargeURL(currencyCode, notifyUrl, state);
        openWebview();
    }

    private void openConsumeSPWebview(int consume_spCoin, String orderNo, String GameName, String productName, String _notifyUrl, String state, String requestNumber) {
        _connectTool.getConsumeSPURL(consume_spCoin, orderNo, GameName, productName, _notifyUrl, state, requestNumber);
        openWebview();
    }

    private void openWebview() {
        Log.v("Test", "openWebview");
        this.runOnUiThread(new Runnable() {
            @SuppressLint("JavascriptInterface")
            @Override
            public void run() {
                _connectTool.initConnectWebview(connect17dameActivity, _connectTool.page_url);
            }
        });
    }
    // endregion ****************** 17dame tool open Webview ********************************

    @Override
    public void onDestroy() {
        super.onDestroy();
        // region ****************** 17dame tool ********************************
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.UPSIDE_DOWN_CAKE) {
            // 修正 Android 14+ 的廣播註冊
            this.registerReceiver(connectReceiver, itFilter, RECEIVER_EXPORTED);
        } else {
            unregisterReceiver(connectReceiver);
        }
        // endregion ****************** 17dame tool ********************************
    }
}
