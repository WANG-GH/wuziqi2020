#pragma once
enum Turns {		//ö�����ͣ�Ĭ�����ǰ��壬��������������Ϊ1������Ϊ-1
	WHITE = 1, BLACK = -1
};

enum Edge_Status {
	BLOCK = -1, EMPTY = 0
};

enum Score {
	ONE = 10,
	TWO = 100,
	THREE = 1000,
	FOUR = 10000,
	FIVE = 100000,
	BLOCKED_ONE = 1,
	BLOCKED_TWO = 10,
	BLOCKED_THREE = 100,
	BLOCKED_FOUR = 1000,
	NOTHREAT = 0
};

const int BoardMargin = 150;				//����ı߽�
const int BoardOneSize = 90;				//����ļ��
const int BoardLineLong = 1410;				//����ı߳�
const int BoardLength = 15;

const int DEPTH = 6;
const int INF = 70000;