function jump() {
	var currentPath = window.location.pathname;
	var newUrl = "https://lyuwenhan.github.io" + currentPath;
	window.location.href = newUrl;
	return false;
}
function get() {
	$.getJSON('https://lanpingzhong-fishing.github.io/file/fishing.json', function(jsonData) {
		console.log('Received data:', jsonData);
		var fileList = jsonData.file;
		var contributionElement = document.querySelector('.contribution');
		fileList.forEach(function(file) {
		  var linkElement = document.createElement('a');
		  linkElement.textContent = file.name;
		  linkElement.href = file.path;
		  contributionElement.parentNode.insertBefore(linkElement, contributionElement);
		  contributionElement.parentNode.insertBefore(document.createElement('br'), contributionElement);
		});
	})
}
function get2() {
	$.getJSON('https://lanpingzhong-fishing.github.io/file/fishing_delete.json', function(jsonData) {
		console.log('Received data:', jsonData);
		var fileList = jsonData.file;
		var contributionElement = document.querySelector('.contribution');
		fileList.forEach(function(file) {
		  var linkElement = document.createElement('a');
		  linkElement.textContent = file.name + " deleted";
		  linkElement.href = file.path;
		  contributionElement.parentNode.insertBefore(linkElement, contributionElement);
		  contributionElement.parentNode.insertBefore(document.createElement('br'), contributionElement);
		});
	})
}