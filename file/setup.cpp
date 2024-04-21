#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <filesystem>
using std::cout;
using std::cerr;
using std::ostream;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::getline;
using std::pair;
using std::istringstream;
using std::to_string;
vector<pair<string, string>> all;
vector<string> now;
string start;
struct endline{}endl;
inline ostream& operator<<(ostream& out, endline e){
	out.flush();
	out << '\r' << std::endl;
	return out;
}
inline bool directoryExists(const char* path) {
	struct stat info;
	if(stat(path, &info) != 0){
		return false;
	}else if(info.st_mode & S_IFDIR){
		return true;
	}else{
		return false;
	}
}
inline vector<pair<string, string>> read_all_list(){
	while(!all.empty()){
		all.pop_back();
	}
	system("mkdir files >/dev/null 2>&1");
	if(!directoryExists("files")){
		cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	system("mkdir files/games >/dev/null 2>&1");
	if(!directoryExists("files/games")){
		cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	ifstream infile("files/all_list.txt");
	if(!infile.good()){
		return all;
	}
	string line;
	while(getline(infile, line)){
		string name, path;
		istringstream iss(line);
		iss >> name >> path;
		path = "lyuwenhan.github.io" + path;
		all.push_back({name, path});
	}
	infile.close();
	return all;
}
inline vector<string> read_now_list(){
	while(!now.empty()){
		now.pop_back();
	}
	ifstream infile("files/downloaded.txt");
	if(!infile.good()){
		infile.close();
		system("touch files/downloaded.txt >/dev/null 2>&1");
		return now;
	}
	string line;
	while(getline(infile, line)){
		now.push_back(line);
	}
	infile.close();
	return now;
}
inline bool get_all_list(){
	system("mkdir files >/dev/null 2>&1");
	if(!directoryExists("files")){
		cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	system("mkdir files/games >/dev/null 2>&1");
	if(!directoryExists("files/games")){
		cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	bool b = system("wget -O files/all_list.txt https://lyuwenhan.github.io/file/list.txt >/dev/null 2>&1");
	read_all_list();
	read_now_list();
	return !b;
}
inline string read_start(){
	system("mkdir files >/dev/null 2>&1");
	if(!directoryExists("files")){
		cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	system("mkdir files/games >/dev/null 2>&1");
	if(!directoryExists("files/games")){
		cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	ifstream infile("files/start.txt");
	if(!infile.good()){
		infile.close();
		system("touch files/start.txt >/dev/null 2>&1");
		start = "";
		return "";
	}
	infile >> start;
	return start;
}
inline void clear(){
	system("clear");
}
inline char getch(){
	char c = getchar();
	if(c == 3){
		clear();
		cout << "^C" << endl;
		system("stty echo cooked");
		exit(1);
	}
	return c;
}
inline void sleep(double time){
	system(((string)"sleep " + to_string(time)).c_str());
}
inline void choose(){
	clear();
	cout << "加载中" << endl;
	clear();
	if(now.empty()){
		cout << "没有已下载的版本" << endl;
		return;
	}
	int choose = 0;
	while(true){
		clear();
		cout << "已下载版本:" << endl;
		for(int i = 0; i < now.size(); i++){
			if(i != choose){
				cout << now[i] << ' ';
			}else{
				cout << "\033[32;1m" << now[i] << "\033[m ";
			}
		}
		cout << endl << "按a和d移动, 按enter确定, 按esc返回" << endl;
		char c = getch();
		while(c != 'a' && c != 'd' && c != '\r' && c != 27){
			c = getch();
		}
		if(c == 'a'){
			choose--;
			if(choose < 0){
				choose = now.size() - 1;
			}
		}else if(c == 'd'){
			choose++;
			if(choose == now.size()){
				choose = 0;
			}
		}else if(c == '\r'){
			ofstream out("files/start.txt");
			out << now[choose] << std::endl;
			start = now[choose];
			return;
		}else{
			return;
		}
	}
}
inline void download(){
	clear();
	cout << "加载中" << endl;
	get_all_list();
	read_now_list();
	read_all_list();
	read_start();
	clear();
	if(all.empty()){
		cout << "没有可下载的版本" << endl;
		return;
	}
	int choose = 0;
	while(true){
		clear();
		cout << "可下载版本:" << endl;
		for(int i = 0; i < all.size(); i++){
			if(i != choose){
				cout << all[i].first << ' ';
			}else{
				cout << "\033[32;1m" << all[i].first << "\033[m ";
			}
		}
		cout << endl << "按a和d移动, 按enter确定, 按esc返回" << endl;
		char c = getch();
		while(c != 'a' && c != 'd' && c != '\r' && c != 27){
			c = getch();
		}
		if(c == 'a'){
			choose--;
			if(choose < 0){
				choose = all.size() - 1;
			}
		}else if(c == 'd'){
			choose++;
			if(choose == all.size()){
				choose = 0;
			}
		}else if(c == '\r'){
			system("mkdir files >/dev/null 2>&1");
			if(!directoryExists("files")){
				cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
				system("stty echo cooked");
				exit(1);
			}
			system("mkdir files/games >/dev/null 2>&1");
			if(!directoryExists("files/games")){
				cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
				system("stty echo cooked");
				exit(1);
			}
			clear();
			cout << "下载中" << endl;
			cout << "完成(0/5)" << endl;
			bool b = system(((string)"wget -O files/" + all[choose].first + ".zip " + all[choose].second + ">/dev/null 2>&1").c_str());
			if(b){
				clear();
				cout << "下载失败" << endl;
				return;
			}
			clear();
			cout << "下载中" << endl;
			cout << "完成(1/5)" << endl;
			{
				std::ofstream out("files/downloaded.txt", std::ios_base::app);
				out << std::endl << all[choose].first << std::endl;
			}
			clear();
			cout << "下载中" << endl;
			cout << "完成(2/5)" << endl;
			system("sort -u files/downloaded.txt -o files/downloaded.txt >/dev/null 2>&1");
			clear();
			cout << "下载中" << endl;
			cout << "完成(3/5)" << endl;
			system(((string)"rm -rf files/games/" + all[choose].first).c_str());
			clear();
			cout << "下载中" << endl;
			cout << "完成(4/5)" << endl;
			system(((string)"unzip files/" + all[choose].first + ".zip -d files/games/ >/dev/null 2>&1").c_str());
			clear();
			cout << "下载成功" << endl;
			return;
		}else{
			return;
		}
	}
}
inline void hand(){
	cout << "这里是手动配置启动项的方法" << endl;
	cout << "1. 把文件放在\"files/games/名称\"" << endl;
	cout << "2. 在\"files/downloaded.txt\"最后添加游戏名称, 需要与第一步创建的文件夹名称相同" << endl;
	cout << "3. 用于启动的文件需要名为\"setup.sh\"或\"setup.out\"或在\"run.txt\"里写出运行文件" << endl;
	cout << "按esc退出" << endl;
	while(getch() != 27);
}
int main(){
	clear();
	system("stty -echo raw");
	system("mkdir files >/dev/null 2>&1");
	if(!directoryExists("files")){
		cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	system("mkdir files/games >/dev/null 2>&1");
	if(!directoryExists("files/games")){
		cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
		system("stty echo cooked");
		exit(1);
	}
	get_all_list();
	read_now_list();
	read_all_list();
	read_start();
	while(true){
		clear();
		read_now_list();
		read_all_list();
		read_start();
		cout << "fishing launcher" << endl << "1.启动当前版本, 2.切换版本, 3.下载其他版本, 4.刷新列表, 5.退出, 6.关于手动配置启动项" << endl << "已下载版本:" << endl;
		if(now.empty()){
			cout << "无" << endl;
		}else{
			for(string i : now){
				cout << i << ' ';
			}
			cout << endl;
		}
		cout << "当前启动版本: " << (start.empty() ? "无" : start) << endl;
		char c = getch();
		while(c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6'){
			c = getch();
		}
		if(c == '1'){
			if(start.empty()){
				cout << "请选择版本" << endl;
				sleep(1);
				continue;
			}
			system("mkdir files >/dev/null 2>&1");
			if(!directoryExists("files")){
				cerr << "保存文件夹缺失, 请手动创建名为\"files\"的文件夹" << endl;
				system("stty echo cooked");
				exit(1);
			}
			system("mkdir files/games >/dev/null 2>&1");
			if(!directoryExists("files/games")){
				cerr << "保存文件夹缺失, 请手动在\"files\"的文件夹下创建名为\"games\"的文件夹" << endl;
				system("stty echo cooked");
				exit(1);
			}
			{
				ofstream out("files/setup.sh");
				out << "cd files/games/" << start << std::endl;
				string name;
				{
					ifstream in("files/games/" + start + "/run.txt");
					if(in.good()){
						string run;
						in >> run;
						ifstream in2("files/games/" + start + "/" + run);
						sleep(1);
						if(in2.good()){
							sleep(1);
							name = run;
						}
					}
				}
				{
					ifstream in("files/games/" + start + "/setup.out");
					if(in.good()){
						name = "setup.out";
					}
				}
				{
					ifstream in("files/games/" + start + "/setup.sh");
					if(in.good()){
						name = "setup.sh";
					}
				}
				if(name.empty()){
					clear();
					cout << "运行文件缺失" << endl;
					sleep(1);
					continue;
				}
				out << "chmod u+x " << name << std::endl;
				out << "./" << name << std::endl;
			}
			system("stty echo cooked");
			system("./files/setup.sh");
			system("stty -echo raw");
			sleep(1);
			continue;
		}else if(c == '2'){
			choose();
			sleep(1);
			continue;
		}else if(c == '3'){
			download();
			sleep(1);
			continue;
		}else if(c == '4'){
			clear();
			cout << "获取中" << endl;
			get_all_list();
			read_now_list();
			read_all_list();
			read_start();
			continue;
		}else if(c == '5'){
			break;
		}else if(c == '6'){
			clear();
			hand();
			continue;
		}
	}
	clear();
	system("stty echo cooked");
	return 0;
}
