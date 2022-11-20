#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
	delete object3d2;
	delete obj;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = ParticleManager::Create();
	//object3d2 = ParticleManager::Create();

	obj = Object3d::Create();
	obj2 = Object3d::Create();

	obj2->trans = { 0.5f,0.0f,0.0f };

	emitter1.init(object3d);

	emitter2.init(object3d);

	emitter2.centerPos = { 2.0f,0.0f,0.0f };
	emitter2.color = { 0.0f,-0.02f,-0.02f,0.0f };
	
}

void GameScene::Update()
{
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		if (input->PushKey(DIK_UP)) { y++; }
		else if (input->PushKey(DIK_DOWN)) { y--; }
		if (input->PushKey(DIK_RIGHT)) { x++; }
		else if (input->PushKey(DIK_LEFT)) { x--; }
		
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }

		if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	if (input->TriggerKey(DIK_R))
	{
		if (sceen == 0)
		{
			sceen++;
		}
		else
		{
			sceen = 0;
		}
	}

	/*object3d->ParticleAdd({}, { 1,1,1 }, { 0.1f,0.1f,0.1f }, { 0,0.001f,0 }, 10, 60,1.0f,0.0f,10.0f,{0.0f,-0.1f,-0.1f,0.0f});
	object3d->ParticleAdd({20,0,0}, { 1,1,1 }, { 0.1f,0.1f,0.1f }, { 0,0.001f,0 }, 10, 60,1.0f,0.0f,10.0f,{-0.1f,-0.1f,0.0f,0.0f});

	object3d->Update(1);*/

	emitter2.centerPos = { x,y,0.0f };

	if (sceen == 1)
	{
		emitter1.ParticleAdd();
		emitter2.ParticleAdd();

		object3d->Update(1);
	}

	if (sceen == 0)
	{
		obj->Update(0);
		obj2->Update(1);
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);
	

	// 3Dオブクジェクトの描画
	if (sceen == 1)
	{
		object3d->Draw();
	}
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
	Object3d::PreDraw(cmdList);
	if (sceen == 0)
	{
		obj->Draw();
		obj2->Draw();
	}
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// 
	/// 
	/// </summary>
	
	debugText.Print("change:R", 0, 0, 1);
	debugText.Print("cameraMove:WASD", 0, 32, 1);
	if (sceen == 1)
	{
		debugText.Print("move:arrow", 0, 42, 1);
	}

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
