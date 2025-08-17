
"object" != typeof ue && (delete window.ue, ue = {});
"object" != typeof ue.webview && (delete ue.webview, ue.webview = {});
"number" != typeof ue.webview.functionid && (delete ue.webview.functionid, ue.webview.functionid = 0);
"string" != typeof ue.webview.name && (delete ue.webview.name, ue.webview.name = 'interface');
"object" != typeof ue.webview.cbarray && (delete ue.webview.cbarray, ue.webview.cbarray = []);
"object" != typeof ue[ue.webview.name] && (delete ue[ue.webview.name], ue[ue.webview.name] = {});
"function" != typeof ue.webview.cbclear && (delete ue.webview.cbclear, ue.webview.cbclear = function () {
    const nowInSeconds = Math.floor(Date.now() / 1000) * 1000000;
    var first = 0;
    var funcid = '';
    while (ue.webview.cbarray.length) {
        first = ue.webview.cbarray[0];
        if (nowInSeconds <= first) {
            break;
        }
        ue.webview.cbarray.shift();
        funcid = `${first}`;
        delete ue[ue.webview.name][funcid];
    }
},setInterval(ue.webview.cbclear,2000));
"function" != typeof ue.webview.register && (delete ue.webview.register, ue.webview.register = function (callback, timeout) {
    if ("function" != typeof callback)
        return "";
    if ("number" != timeout) {
        timeout = 6;
    }
    ue.webview.functionid = ue.webview.functionid + 1;
    var composeid = ue.webview.functionid % 1000000;
    var nowInSeconds = Math.floor(Date.now() / 1000);
    nowInSeconds = (nowInSeconds + timeout) * 1000000 + composeid;
    var funcid = `${nowInSeconds}`
    ue[ue.webview.name][funcid] = callback;
    if (timeout <= 0) {
        return funcid;
    }
    ue.webview.cbarray.push(nowInSeconds);
    return funcid;
});

"function" != typeof ue.webview.asyn && (delete ue.webview.asyn, ue.webview.asyn = function (type, json, cback) {
    if ("object" != typeof ue["$receive"] || "function" != typeof ue["$receive"]["asyn"]) {
        console.error("[ue.$receive.asyn] drop message .... key" + key + " json" + JSON.stringify(json));
        return;
    }
    ue["$receive"].asyn(type, json, cback);
});
// for android platform
"object" == typeof webview_android && (delete ue.webview.asyn, ue.webview.asyn = webview_android.asyn)


// using default call
if ("function" != typeof typeof ue.call) {
    delete ue.call;
    ue.call = function (type, json, cback, timeout) {
        if ("string" !== typeof type) {
            console.error("type of ue.call must be string");
            return;
        }
        var backid = ue.webview.register(cback, timeout);
        if ("string" !== typeof json) {
            ue.webview.asyn(type, JSON.stringify(json), backid);
        }
        else {
            ue.webview.asyn(type, json, backid);
        }
    };
}

"function" != typeof ue4 && (delete window.ue4, ue4 = ue.call);

// document.dispatchEvent(ue.on_call_begin)
// document.addEventListener(ue.on_call_begin, function(e) {
//     console.warn('Begin Send msg to ue');
// });
"string" != ue.on_call_begin && (ue.on_call_begin = 'ue.call.begin.event')

if ('function' != typeof ue.enter_tojs) ue.enter_tojs = function () {
    ue.proxy_tojs(function (func_name, param) {
        var webview_receive_name = ue[ue.webview.name];
        if (func_name in webview_receive_name) {
            webview_receive_name[func_name](JSON.parse(param));
        }
        else {
            console.warn('function ' + func_name + ' do not exists!');
        }
    });
}
