//
//
//
//

var IE4 = (document.all) ? 1 : 0;
var NS4 = (document.layers) ? 1 : 0;
var NS6 = document.getElementById&&!document.all;
var VERSION_OK = (IE4 | NS4 | NS6) ? 1 : 0;
if (!VERSION_OK) event = null;

function ad_GetOffset(obj, coord) {
	var val = obj["offset"+coord] ;
	if (coord == "Top") val += obj.offsetHeight;
	while ((obj = obj.offsetParent )!=null) {
		val += obj["offset"+coord];
		if (obj.border && obj.border != 0) val++;
	}
	return val;
}

function ad_hide () {
	if (IE4) document.all.ad_popup.style.visibility = "hidden";
	if (NS4) document.ad_popup.visibility = "hidden";
	if (NS6) document.getElementById("ad_popup").style.visibility = "hidden";
}

function p (event,texte) {
	if (!VERSION_OK) return;

	var ptrObj, ptrLayer;
	if (IE4) {
		ptrObj = event.srcElement;
		ptrLayer = document.all.ad_popup;
	}
	if (NS4) {
		ptrObj = event.target;
		ptrLayer = document.ad_popup;
	}
	if (NS6) {
		ptrObj = event.target;
		ptrLayer = document.getElementById("ad_popup");
	}

	if (!ptrObj.onmouseout) ptrObj.onmouseout = ad_hide;

	var str = '<DIV CLASS="ad_popupDIV">'+texte+'</DIV>';
    if (IE4 | NS6) {
		ptrLayer.innerHTML = str;
		ptrLayer.style.top  = ad_GetOffset (ptrObj,"Top") + 8;
		ptrLayer.style.left = ad_GetOffset (ptrObj,"Left");
		ptrLayer.style.visibility = "visible";
	}
	if (NS4) {
		ptrLayer.document.write (str);
	    ptrLayer.document.close ();
		ptrLayer.document.bgColor = "yellow";
		ptrLayer.top  = ptrObj.y + 20;
		ptrLayer.left = ptrObj.x;
		ptrLayer.visibility = "show";
	}
}
// -->