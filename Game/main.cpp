/*!
 *@brief	main.cpp
 */
#include "stdafx.h"
#include "Taitor.h"
#include "Fade.h"
#include"Stage.h"
#include"Stage_Light.h"
#include"AI_manager.h"
#include"BGM.h"
#include"Player.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	srand((unsigned)time(NULL));
#ifdef USE_LOW_SPEC_SETTINGS
	//tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1280;
	initParam.screenHeight = 720;
	initParam.frameBufferWidth = 640;
	initParam.frameBufferHeight = 360;
	initParam.screenWidth2D = 1280;
	initParam.screenHeight2D = 720;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 512;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 512;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(100.0f);
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.002f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::enNone;
	//アンチ
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = false;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
#else
	//tkEngine2の初期化パラメータを設定する。
	SInitParam initParam;
	initParam.nCmdShow = nCmdShow;
	initParam.hInstance = hInstance;
	initParam.screenWidth = 1920;
	initParam.screenHeight = 1080;
	initParam.frameBufferWidth = 1920;
	initParam.frameBufferHeight = 1080;
	//影の設定。
	initParam.graphicsConfing.shadowRenderConfig.isEnable = true;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapWidth = 2048;
	initParam.graphicsConfing.shadowRenderConfig.shadowMapHeight = 2048;
	initParam.graphicsConfing.shadowRenderConfig.lightHeight = UnitM(100.0f);
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[0] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[1] = 0.001f;
	initParam.graphicsConfing.shadowRenderConfig.depthOffset[2] = 0.002f;
	initParam.graphicsConfing.shadowRenderConfig.softShadowLevel = EnSoftShadowQualityLevel::eSSSS_PCF;
	//アンチ
	initParam.graphicsConfing.aaConfig.isEnable = true;
	//Bloom
	initParam.graphicsConfing.bloomConfig.isEnable = true;
	//tonemap
	initParam.graphicsConfing.tonemapConfig.isEnable = true;
#endif
	GraphicsEngine().GetShadowMap().SetFar(1000.0f);
	GraphicsEngine().GetShadowMap().SetNear(50.0f);

	//エンジンを初期化。
	if (Engine().Init(initParam) == true) {

		NewGO<Taitor>(0, "Taitor");
		NewGO<Fade>(1, "Fade");
		NewGO<Stage_Light>(0, "Light");
		NewGO<AI_manager>(0, "AI_manager");
		NewGO<Stage>(0, "stage");
		NewGO<Player>(0, "Player");
		NewGO<BGM>(0, "BGM");
		GraphicsEngine().GetMonochrome().SetAlpha(0.0f);
		//ゲームループを実行。
		Engine().RunGameLoop();
	}
	//エンジンの終了処理。
	Engine().Final();

	return 0;
}

