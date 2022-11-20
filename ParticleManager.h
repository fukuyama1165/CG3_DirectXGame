#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <forward_list>

enum ParticleAddSplit
{
	minusSplit,
	centerSplit,
	plusSplit
};

enum blendMode
{
	blendModeAlpha,
	blendModeAdd,
	blendModeSub,

};

/// <summary>
/// 3Dオブジェクト
/// </summary>
class ParticleManager
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 頂点データ構造体
	//struct VertexPosNormalUv
	//{
	//	XMFLOAT3 pos; // xyz座標
	//	XMFLOAT3 normal; // 法線ベクトル
	//	XMFLOAT2 uv;  // uv座標
	//};

	struct VertexPos
	{
		XMFLOAT3 pos; // xyz座標
		float scale;//スケール
		float rotate;//回転
		XMFLOAT4 color;//色
	};

	// 定数バッファ用データ構造体
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
		XMMATRIX matBillboard;
	};

	struct Particle
	{
		using XMFLOAT3 = DirectX::XMFLOAT3;

		//座標
		XMFLOAT3 position = {};

		//速度
		XMFLOAT3 velocity = {};

		//加速度
		XMFLOAT3 accel = {};

		//現在フレーム
		int frame = 0;

		//終了フレーム
		int numFrame = 0;

		//スケール
		float scale = 1.0f;

		//初期値
		float sScale = 1.0f;

		//最終値
		float eScale = 0.0f;

		//角度(Z軸)
		float rotate = 0.0f;

		float addRotate = 0.0f;

		//色
		XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

		XMFLOAT4 addColor = { 0.0f,0.0f,0.0f,0.0f };

	};

private: // 定数
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = 1024;// 頂点数
	//static const int indexCount = 3 * 2;//インデックス数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static ParticleManager* Create();

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveVector(XMFLOAT3 move);

	/// <summary>
	/// ベクトルによる視点移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveEyeVector(XMFLOAT3 move);

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// 頂点バッファ
	static ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	//static ComPtr<ID3D12Resource> indexBuff;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;
	// 頂点バッファビュー
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	//static D3D12_INDEX_BUFFER_VIEW ibView;
	// 頂点データ配列
	static VertexPos vertices[vertexCount];
	// 頂点インデックス配列
	//static unsigned short indices[indexCount];

	//ビルボード行列
	static XMMATRIX matBillboard;

	//Y軸周りビルボード行列
	static XMMATRIX matBillboardY;

private:// 静的メンバ関数
	/// <summary>
	/// デスクリプタヒープの初期化
	/// </summary>
	static void InitializeDescriptorHeap();

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();
	static void InitializeGraphicsPipeline2();
	static void InitializeGraphicsPipeline3();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	static void LoadTexture();

	/// <summary>
	/// モデル作成
	/// </summary>
	static void CreateModel();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

public: // メンバ関数
	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update(int BillboardFlag=0);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 座標の取得
	/// </summary>

	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,float startScale,float endScale,float rotate,XMFLOAT4 color);

	/// <summary>
	/// パーティクル発生
	/// </summary>
	/// <param name="centerPos">発生する中心座標</param>
	/// <param name="addPosWidth">出てくる場所の幅</param>
	/// <param name="addVelocityWidth">出てくる速度の幅</param>
	/// <param name="addAccelWidth">出てくる加速度の幅</param>
	/// <param name="particleNum">一度に出す量</param>
	/// <param name="particleLife">パーティクルの生存時間</param>
	/// <param name="startScale">初めのスケール</param>
	/// <param name="endScale">終わった時のスケール</param>
	/// <param name="rotate">回転角度増加量</param>
	/// <param name="color">色合い</param>
	/// <param name="posSplit">座標のランダムをどちらに寄せるか minusSplit =マイナス寄り,centerSplit=半分,plusSplit=プラス寄り</param>
	/// <param name="velocitySplit">速度のランダムをどちらに寄せるか minusSplit =マイナス寄り,centerSplit=半分,plusSplit=プラス寄り</param>
	/// <param name="accelSplit">加速度のランダムをどちらに寄せるか minusSplit =マイナス寄り,centerSplit=半分,plusSplit=プラス寄り</param>
	void ParticleAdd(XMFLOAT3 centerPos, XMFLOAT3 addPosWidth, XMFLOAT3 addVelocityWidth, XMFLOAT3 addAccelWidth, int particleNum,int particleLife, float startScale, float endScale, float rotate, XMFLOAT4 color,int posSplit = centerSplit, int velocitySplit = centerSplit, int accelSplit = minusSplit);
	

	void setBlend(int blendMode);

private: // メンバ変数
	ComPtr<ID3D12Resource> constBuff; // 定数バッファ
	// 色

	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	
	std::forward_list<Particle> particles;

	// ローカル座標
	
	// ローカルワールド変換行列
	
	// 親オブジェクト
	
};

