function jump() {
	var currentPath = window.location.pathname;
	var newUrl = "https://lyuwenhan.github.io" + currentPath;
	window.location.href = newUrl;
	return false;
}
function jump() {
	var currentPath = window.location.pathname;
	var newUrl = "https://lyuwenhan.github.io" + currentPath;
	window.location.href = newUrl;
	return false;
}
function remove_to_back(url) {
    // 使用 split() 函数将 URL 按照斜杠分割成数组
    var segments = url.split('/');
    
    // 如果数组长度小于等于1，表示没有路径或者只有根路径，直接返回原始URL
    if (segments.length <= 1) {
        return url;
    }
    
    // 弹出数组的最后一个元素（即路径的最后一项）
    segments.pop();
    
    // 使用 join() 函数将数组重新组合成字符串，再添加斜杠连接
    return segments.join('/');
}

function jump_back() {
	var currentPath = window.location.pathname;
	// console.log(remove_to_back(remove_to_back(currentPath)));
	window.location.href = remove_to_back(remove_to_back(currentPath));
	return false;
}