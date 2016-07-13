#include"Object.h"
#include"InputKey.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定


	MyMath::Physics<double> left_top;
	left_top.x = 200;
	left_top.y = 200;
	MyMath::Physics<double> right_under;
	right_under.x = 400;
	right_under.y = 400;
	Object* obj = new Object(left_top, right_under);

	MyMath::Physics<int> mouse;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && KeyBoard::gpUpdateKey() == 0){
		GetMousePoint(&mouse.x, &mouse.y);
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			DrawCircle(mouse.x, mouse.y, (int)MOUSE_RANGE, RED, FALSE);
			obj->Move_Node(mouse);
		}
		obj->Calc_U_Vec();
		obj->Draw();
	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}