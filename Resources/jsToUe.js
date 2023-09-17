
// create the global ue4(...) helper function
//"object"!=typeof ue&&(ue={}),uuidv4=function(){return"10000000-1000-4000-8000-100000000000".replace(/[018]/g,function(t){return(t^crypto.getRandomValues(new Uint8Array(1))[0]&15>>t/4).toString(16)})},ue4=function(r){return"object"!=typeof ue.interface||"function"!=typeof ue.interface.broadcast?(ue.interface={},function(t,e,n,o){var u,i;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=[t,"",r(n,o)],void 0!==e&&(u[1]=e),i=encodeURIComponent(JSON.stringify(u)),"object"==typeof history&&"function"==typeof history.pushState?(history.pushState({},"","#"+i),history.pushState({},"","#"+encodeURIComponent("[]"))):(document.location.hash=i,document.location.hash=encodeURIComponent("[]")))}):(i=ue.interface,ue.interface={},function(t,e,n,o){var u;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=r(n,o),void 0!==e?i.broadcast(t,JSON.stringify(e),u):i.broadcast(t,"",u))});var i}(function(t,e){if("function"!=typeof t)return"";var n=uuidv4();return ue.interface[n]=t,setTimeout(function(){delete ue.interface[n]},1e3*Math.max(1,parseInt(e)||0)),n});
"object"!=typeof ue&&(ue={}),
ue4=function(functoid)
    {
         "object"!=typeof ue.interface && (delete ue.interface,ue.interface={});
         return function(key,json,cback,timeout){
                   if( "object"!=typeof ue["$receive"] || "function"!=typeof ue["$receive"]["asyn"]){
                    console.error("[ue.$receive.asyn] drop message .... key"+key+" json"+JSON.stringify(json));
                    return ;
                   }
                   "string"==typeof key&&("function"==typeof json&&(timeout=cback,cback=json,json=null));
                   var backid=functoid(cback,timeout);
                   void "string"!==typeof json?ue["$receive"].asyn(key,JSON.stringify(json),backid):ue["$receive"].asyn(key,json,backid);
                } ;
    }(
        function(callback,timeout){
            if("function"!=typeof callback)
                return"";
            var funcid=function(){return"10000000-1000-4000-8000-100000000000".replace(/[018]/g,function(t){return(t^crypto.getRandomValues(new Uint8Array(1))[0]&15>>t/4).toString(16)})}();
            return ue.interface[funcid]=callback,setTimeout(function(){delete ue.interface[funcid]},1e3*Math.max(2,parseInt(timeout)||0)),funcid
        }
    );
//"object"!=typeof unreal&&(unreal={}),uuidv4=function(){return"10000000-1000-4000-8000-100000000000".replace(/[018]/g,function(t){return(t^crypto.getRandomValues(new Uint8Array(1))[0]&15>>t/4).toString(16)})},ue4=function(r){return"object"!=typeof unreal.interface||"function"!=typeof unreal.interface.broadcast?(unreal.interface={},function(t,e,n,o){var u,i;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=[t,"",r(n,o)],void 0!==e&&(u[1]=e),i=encodeURIComponent(JSON.stringify(u)),"object"==typeof history&&"function"==typeof history.pushState?(history.pushState({},"","#"+i),history.pushState({},"","#"+encodeURIComponent("[]"))):(document.location.hash=i,document.location.hash=encodeURIComponent("[]")))}):(i=unreal.interface,unreal.interface={},function(t,e,n,o){var u;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=r(n,o),void 0!==e?i.broadcast(t,JSON.stringify(e),u):i.broadcast(t,"",u))});var i}(function(t,e){if("function"!=typeof t)return"";var n=uuidv4();return unreal.interface[n]=t,setTimeout(function(){delete unreal.interface[n]},1e3*Math.max(1,parseInt(e)||0)),n});
//"object"!=typeof unreal&&(unreal={}),uuidv4=function(){return"10000000-1000-4000-8000-100000000000".replace(/[018]/g,function(t){return(t^crypto.getRandomValues(new Uint8Array(1))[0]&15>>t/4).toString(16)})},ue4=function(r){return"object"!=typeof unreal.interface||"function"!=typeof unreal.interface.synccallue?(unreal.interface={},function(t,e,n,o){var u,i;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=[t,"",r(n,o)],void 0!==e&&(u[1]=e),i=encodeURIComponent(JSON.stringify(u)),"object"==typeof history&&"function"==typeof history.pushState?(history.pushState({},"","#"+i),history.pushState({},"","#"+encodeURIComponent("[]"))):(document.location.hash=i,document.location.hash=encodeURIComponent("[]")))}):(i=unreal.interface,unreal.interface={},function(t,e,n,o){var u;"string"==typeof t&&("function"==typeof e&&(o=n,n=e,e=null),u=r(n,o),void 0!==e?i.synccallue(t,JSON.stringify(e),u):i.synccallue(t,"",u))});var i}(function(t,e){if("function"!=typeof t)return"";var n=uuidv4();return unreal.interface[n]=t,setTimeout(function(){delete unreal.interface[n]},1e3*Math.max(1,parseInt(e)||0)),n});

