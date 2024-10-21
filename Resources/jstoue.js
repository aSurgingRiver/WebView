
"object"!=typeof ue &&(delete ue ,ue={});
"object" != typeof ue.interface && (delete ue.interface , ue.interface={});
"function" != typeof ue.call && (ue.call = function (functoid) {
    return function (key, json, cback, timeout) {
        if ("object" != typeof ue["$receive"] || "function" != typeof ue["$receive"]["asyn"]) {
            console.error("[ue.$receive.asyn] drop message .... key" + key + " json" + JSON.stringify(json));
            return;
        }
        "string" == typeof key && ("function" == typeof json && (timeout = cback, cback = json, json = null));
        var backid = functoid(cback, timeout);
        void "string" !== typeof json ? ue["$receive"].asyn(key, JSON.stringify(json), backid) : ue["$receive"].asyn(key, json, backid);
    };
}(
    function (callback, timeout) {
        if ("function" != typeof callback)
            return "";
        var funcid = function () { return "10000000-1000-4000-8000-100000000000".replace(/[018]/g, function (t) { return (t ^ crypto.getRandomValues(new Uint8Array(1))[0] & 15 >> t / 4).toString(16) }) }();
        return ue.interface[funcid] = callback, setTimeout(function () { delete ue.interface[funcid] }, 1e3 * Math.max(2, parseInt(timeout) || 0)), funcid
    }
));
"function" != typeof ue4 && (delete ue4, ue4=ue.call);
