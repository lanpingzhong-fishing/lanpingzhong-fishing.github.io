function jump() {
	var currentPath = window.location.pathname;
	var newUrl = "https://lyuwenhan.github.io" + currentPath;
	window.location.href = newUrl;
	return false;
}