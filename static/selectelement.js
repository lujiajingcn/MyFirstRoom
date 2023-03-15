function get_current_element(event){
	var x = event.clientX, y = event.clientY,
	element = document.elementFromPoint(x, y);
	return element
}

var last_element = null
function track_mouse(event){
	var elementMouseIsOver = get_current_element(event)
	if (elementMouseIsOver === last_element) {
		return
	}
	if (last_element != null) {
		remove_hightlight(last_element)
	}

	highlight(elementMouseIsOver)
	last_element = elementMouseIsOver
}

function highlight(element){
	element.style.outline = '#f00 solid 2px'
}

function remove_hightlight(element){
	element.style.removeProperty('outline')
}
window.onmousemove = track_mouse

document.onclick = function(){
	var s_json = parase_template(last_element);
	sendMessage(s_json);
};
