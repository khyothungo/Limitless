/* Cydia - iPhone UIKit Front-End for Debian APT
 * Copyright (C) 2008-2011  Jay Freeman (saurik)
*/

/* Modified BSD License {{{ */
/*
 *        Redistribution and use in source and binary
 * forms, with or without modification, are permitted
 * provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the
 *    above copyright notice, this list of conditions
 *    and the following disclaimer in the documentation
 *    and/or other materials provided with the
 *    distribution.
 * 3. The name of the author may not be used to endorse
 *    or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/* }}} */

#ifndef CyteKit_WebViewController_H
#define CyteKit_WebViewController_H

#include "CyteKit/ViewController.h"
#include "CyteKit/WebView.h"

#include <UIKit/UIKit.h>
#include <MessageUI/MessageUI.h>

#include <Menes/ObjectHandle.h>

@class IndirectDelegate;

@protocol CyteWebViewControllerDelegate
- (void) retainNetworkActivityIndicator;
- (void) releaseNetworkActivityIndicator;
- (CyteViewController *) pageForURL:(NSURL *)url forExternal:(BOOL)external;
- (void) unloadData;
@end

@interface CyteWebViewController : CyteViewController <
    CyteWebViewDelegate,
    MFMailComposeViewControllerDelegate,
    UIWebViewDelegate
> {
    _H<CyteWebView, 1> webview_;
    _transient UIScrollView *scroller_;

    _H<UIActivityIndicatorView> indicator_;
    _H<IndirectDelegate, 1> indirect_;
    _H<NSURLAuthenticationChallenge> challenge_;

    bool error_;
    _H<NSURLRequest> request_;
    bool ready_;

    _H<NSURLRequest> stage1_;
    _H<NSURLRequest> stage2_;

    _transient NSNumber *sensitive_;

    _H<NSString> title_;
    _H<NSMutableSet> loading_;

    // XXX: NSString * or UIImage *
    _H<NSObject> custom_;
    _H<NSString> style_;

    _H<WebScriptObject> function_;

    float width_;
    Class class_;

    _H<UIBarButtonItem> reloaditem_;
    _H<UIBarButtonItem> loadingitem_;

    bool visible_;
    bool hidesNavigationBar_;
    bool allowsNavigationAction_;
}

+ (void) _initialize;

- (CyteWebView *) webView;

- (void) setURL:(NSURL *)url;

- (void) loadURL:(NSURL *)url cachePolicy:(NSURLRequestCachePolicy)policy;
- (void) loadURL:(NSURL *)url;

- (void) loadRequest:(NSURLRequest *)request;
- (bool) isLoading;

- (void) reloadURLWithCache:(BOOL)cache;
- (void) reloadURL;

- (id) init;
- (id) initWithURL:(NSURL *)url;
- (id) initWithWidth:(float)width;
- (id) initWithWidth:(float)width ofClass:(Class)_class;

- (void) callFunction:(WebScriptObject *)function;

- (void) webView:(WebView *)view didClearWindowObject:(WebScriptObject *)window forFrame:(WebFrame *)frame;
- (NSURLRequest *) webView:(WebView *)view resource:(id)identifier willSendRequest:(NSURLRequest *)request redirectResponse:(NSURLResponse *)response fromDataSource:(WebDataSource *)source;

+ (float) defaultWidth;

- (void) setButtonImage:(NSString *)button withStyle:(NSString *)style toFunction:(id)function;
- (void) setButtonTitle:(NSString *)button withStyle:(NSString *)style toFunction:(id)function;
- (void) setHidesNavigationBar:(bool)value;

- (void) alertView:(UIAlertView *)alert clickedButtonAtIndex:(NSInteger)button;
- (void) customButtonClicked;

- (void) applyRightButton;
- (UIBarButtonItem *) customButton;
- (UIBarButtonItem *) rightButton;

- (void) applyLeftButton;
- (UIBarButtonItem *) leftButton;

- (void) _didStartLoading;
- (void) _didFinishLoading;

- (void) close;

- (void) dispatchEvent:(NSString *)event;

- (void) setViewportWidthOnMainThread:(float)value;

@end

#endif//CyteKit_WebViewController_H