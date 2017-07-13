#pragma once

#include<iostream>
using namespace std;
class Song {
private:
	string Songname;
	string Singername;
	string path;
	int Time;
public:
	string GetSongname() {
		return Songname;
	}
	string GetSingername() {
		return Singername;
	}
	string Getpath() {
		return path;
	}
	int GetTime() {
		return Time;
	}
	void SetSongname(string name) {
		Songname = name;
	}
	void Setpath(string path) {
		this->path = path;
	}
};