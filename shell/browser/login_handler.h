// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef SHELL_BROWSER_LOGIN_HANDLER_H_
#define SHELL_BROWSER_LOGIN_HANDLER_H_

#include "base/strings/string16.h"
#include "base/values.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/login_delegate.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {
class WebContents;
}

namespace electron {

// Handles HTTP basic auth.
class LoginHandler : public content::LoginDelegate,
                     public content::WebContentsObserver {
 public:
  LoginHandler(const net::AuthChallengeInfo& auth_info,
               content::WebContents* web_contents,
               bool is_main_frame,
               const GURL& url,
               scoped_refptr<net::HttpResponseHeaders> response_headers,
               bool first_auth_attempt,
               LoginAuthRequiredCallback auth_required_callback);
  ~LoginHandler() override;

 private:
  void EmitEvent(net::AuthChallengeInfo auth_info,
                 bool is_main_frame,
                 const GURL& url,
                 scoped_refptr<net::HttpResponseHeaders> response_headers,
                 bool first_auth_attempt);
  void CallbackFromJS(base::string16 username, base::string16 password);

  LoginAuthRequiredCallback auth_required_callback_;

  base::WeakPtrFactory<LoginHandler> weak_factory_{this};

  DISALLOW_COPY_AND_ASSIGN(LoginHandler);
};

}  // namespace electron

#endif  // SHELL_BROWSER_LOGIN_HANDLER_H_
