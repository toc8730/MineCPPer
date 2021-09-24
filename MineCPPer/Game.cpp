#include <vector>
#include <string>
#include <fstream>
#include <ddstream.h>
#include <WinBase.h>
#include <filesystem>
class Game {
	class TileData {
		public: bool isMine;
		public: int numSurrounding;
		public: bool revealed;
	};
	class BoardData {
		public: std::vector<std::vector<TileData>> tiles;
	};
	enum GameMode { EASY, MEDIUM, HARD };
	GameMode gameMode;
	void save(BoardData boardData) {
		char oldCurrDir[_MAX_DIR];
		char path[_MAX_DIR];
		char newPath[_MAX_DIR];
		char savesPath[_MAX_DIR];
		GetCurrentDirectory(_MAX_DIR, LPWSTR(oldCurrDir)); // stores current directory in oldCurrDir
		strcpy(path, oldCurrDir); // copying oldCurrDir into path
		strcat(path, "/MineCPPer"); // path = oldCurrDir + "/MineCPPer"
		if (CreateDirectory(LPCWSTR(path), NULL) != 0)
		{
			GetCurrentDirectory(_MAX_DIR, LPWSTR(path));
			strcat(path, "/MineCPPer.exe");
			strcpy(newPath, oldCurrDir);
			strcat(newPath, "/MineCPPer/MineCPPer.exe");
			std::rename(path, newPath); // moving the exe
			strcpy(savesPath, oldCurrDir);
			strcat(savesPath, "/MineCPPer/saves");
			CreateDirectory(LPCWSTR(path), NULL);
		}
		switch (gameMode) {
			case GameMode::EASY :
				strcat(savesPath, "/easy.minesaver");
				break;
			case GameMode::MEDIUM :
				strcat(savesPath, "/medium.minesaver");
				break;
			case GameMode::HARD :
				strcat(savesPath, "/hard.minesaver");
				break;
		}
		HANDLE file = CreateFile(LPCWSTR(savesPath), GENERIC_WRITE, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		char saveData[20];
		int bytesWritten;
		for (std::vector<TileData> inner : boardData.tiles)
			for (TileData tileData : inner)
			{
				strcpy(saveData, std::to_string(tileData.isMine).c_str());
				strcat(saveData, std::to_string(tileData.numSurrounding).c_str());
				strcat(saveData, std::to_string(tileData.revealed).c_str());
				WriteFile(file, LPCVOID(saveData), DWORD(sizeof(saveData)), LPDWORD(bytesWritten), NULL);
			}
	}
	void load(BoardData boardData) {

	}
};