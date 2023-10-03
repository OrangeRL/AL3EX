#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<random>
#include"AxisIndicator.h"
#include"PrimitiveDrawer.h"
#include"DebugCamera.h"
#include "Player.h"


GameScene::GameScene() {

}

GameScene::~GameScene() {
	delete modelManager;
	delete enemyManager;
	delete asteroidManager;
	delete toManager;
	delete spManager;
	delete model_;
	//delete debugCamera_;
	delete player_;
	delete modelSkydome_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	//textureHandle_ = TextureManager::Load("player.png");
	modelManager = new ModelManager();
	model_ = Model::Create();
	spriteTimer = Sprite::Create(TextureManager::Load("overTimer.png"),
		{ 0,0 });
	spriteTimer->SetSize({ 100 * 1.3f, 100 * 1.3f });
	spriteTimer->SetPosition({ -15,
			-35
		});
	//SDManager.Initialize();
	titleBGM = audio_->LoadWave("Outset.wav");
	desertBGM = audio_->LoadWave("Stage1.wav");
	carFX = audio_->LoadWave("carRev.wav");
	hitFX = audio_->LoadWave("OnHit.wav");
	audio_->PlayWave(titleBGM, true, 0.1f);
	


	title.Initialize(modelManager->titleCar, modelManager->titleCar, modelManager->titleCar, titleView);
	titleView.Initialize();
	titleView.fovAngleY = DegreeConversionRad(90.0f);
	//アスペクト比
	titleView.aspectRatio = 1.0f;

	Vector3 position = worldTransforms_->translation_;
	//自キャラの生成
	player_ = new Player();
	/*player_->Initialize(model_, textureHandle_);*/
	if (scene == 1) {
		modelSkydome_ = Model::CreateFromOBJ("Jam", true);
	}
	if (scene == 2) {
		modelSkydome_ = Model::CreateFromOBJ("skydome2", true);
	}

	TextureHandle white = TextureManager::Load("white.png");

	enemyManager = new EnemyManager(
		modelManager->rakuda,
		modelManager->model_,
		white
	);

	asteroidManager = new AsteroidManager(
		modelManager->star,
		modelManager->star,
		white
	);

	toManager = new TitleObaManager(
		modelManager->titleStar,
		modelManager->titleStar,
		white
	);
	to2Manager = new TitleObaManager(
		modelManager->titleRakuda,
		modelManager->titleRakuda,
		white
	);
	to3Manager = new TitleObaManager(
		modelManager->titleOba,
		modelManager->titleOba,
		white
	);
	to4Manager = new TitleObaManager(
		modelManager->signalPole,
		modelManager->signalPole,
		white
	);

	spManager = new SpeedParticleManager(
		modelManager->gas,
		modelManager->gas,
		white
	);
	
	bManager.Initialize(modelManager->model_);
	gManager.Initialize(modelManager->model_);
	pedestrianManager.Initialize(modelManager->model_);
	windManager.Initialize(modelManager->model_);
	crossManager.Initialize(modelManager->model_);
	player_->SetSpawnPos(gManager.GetSpawnPos());

	
	player_->Initialize(
		modelManager->player,
		modelManager->body,
		modelManager->carWindow,
		railCamera_->GetWorldMatrix(),
		Vector3(0.0f, 0.0f, 50.0f));
	

	signal.Initialize(model_, model_, model_);
	signalManager.Initialize(modelManager->signalPole, modelManager->signalLight, modelManager->signalLamp);

	pyramidManager.Initialize(modelManager->pyramid, modelManager->pyramid, modelManager->pyramid);
	camelManager.Initialize(modelManager->rakuda, modelManager->rakuda, modelManager->rakuda);
	//tekiキャラの生成

	enemy_ = new Enemy();
	////敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

	enemy_->Initialize(modelManager->goal, modelManager->brake, { 0.0f,1.4f,10.0f }, textureHandle_);


	title_ = new Title();
	title_->Initialize(model_, textureHandle_);

	victory_ = new Victory();
	victory_->Initialize(model_, textureHandle_);

	skydome_ = std::make_unique<skydome>();
	skydomee_ = std::make_unique<skydome>();
	skydomeee_ = std::make_unique<skydome>();
	//3Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	modelSkydomee_ = Model::CreateFromOBJ("Jam", true);
	modelSkydomeee_ = Model::CreateFromOBJ("skydome2", true);

	skydome_->Initialize(modelSkydome_);
	skydomee_->Initialize(modelSkydomee_);
	skydomeee_->Initialize(modelSkydomeee_);
	//レールカメラの生成
	railCamera_ = std::make_unique<RailCamera>();

	railCamera_->Initialize(Vector3(0.0f, 0.0f, -50.0f), Vector3(0.0f, 0.0f, 0.0f));
	player_->SetParent(railCamera_->GetWorldMatrix());
	//デバックカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	//AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する (アドレス渡し)
	//AxisIndicator::SetTargetViewProjection(&viewProjection_);

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

}
void GameScene::OverTimerReset() {
	if (scene == 1) {
	overTimer = 1500;
	}
	if (scene == 2) {
		overTimer = 2100;
	}
	if (scene == 3) {
		overTimer = 1500;
	}
}
void GameScene::Update() {


	popPos = { 0,0,0 };
	if (scene == -1 || scene == 0 || scene == 4) {
		toManager->Update(popPos, bManager.IsBossBattle(), audio_, SDManager);
		toManager->EventStart(audio_, SDManager);
		to2Manager->Update(popPos, bManager.IsBossBattle(), audio_, SDManager);
		to2Manager->EventStart(audio_, SDManager);
		to3Manager->Update(popPos, bManager.IsBossBattle(), audio_, SDManager);
		to3Manager->EventStart(audio_, SDManager);
		to4Manager->Update(popPos, bManager.IsBossBattle(), audio_, SDManager);
		to4Manager->EventStart(audio_, SDManager);
		player_->Reset();
	}

	//debugCamera_->Update();
	
	
	title.Update();
	//title_->Update();
	skydome_->Update();
	skydomee_->Update2();
	//debugText_->SetPos(50, 200);
	//debugText_->Printf("scene:%d", scene);
	if(scene <= 0 || scene == 4){
	if (input_->TriggerKey(DIK_T))
	{
		if (scene == -1) {
			//audio_->StopWave(titleBGM);
			selectFX = audio_->LoadWave("selectSound.wav");
			audio_->PlayWave(selectFX, false, 0.1f);
		}
		if (scene == 0) {
			carFX = audio_->LoadWave("carRev.wav");
			selectFX = audio_->LoadWave("selectSound.wav");
			audio_->PlayWave(selectFX, false, 0.1f);
			audio_->StopWave(titleBGM);
			//audio_->PlayWave(carFX, true, 0.02f);
			
			audio_->PlayWave(desertBGM, true, 0.1f);
			//audio_->PlayWave(titleBGM, true, 0.1f);
		}
	
		if (scene == 4)
		{
			audio_->StopWave(desertBGM);
			audio_->PlayWave(titleBGM, true, 0.1f);
			scene = -1;
		}
		overTimer = 1500;
		//isStart_ = true;
		scene += 1;

		//player_->resetStage();
		//player_->Reset();
		for (int i = 0; i < 1; i++) {
			pBoostUse = false;
			player_->resetStage();
			
			victory_->Restart();
			player_->Reset();
			enemy_->Reset();
			railCamera_->Restart();
			gManager.Update();
			//bullet->OnCollision();
			isRestart_ = true;
			
			break;


			if (isRestart_ == true) {
				isStart_ = false;
				isRestart_ = false;
				break;
			}
		}
	}
	}

	if (scene == 1) {
		if(playerDead==false)
		{
		overTimer--;
		}
		//自キャラの更新
		spManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		spManager->EventStart(audio_, SDManager);
		player_->Update();
		//敵の更新
		enemy_->Update();
		victory_->Update();
		railCamera_->Update();
		gManager.Update();
		bManager.Update();
		pedestrianManager.Update();
		crossManager.Update();
		signalManager.Update();
		if (overTimer <= 0) {
			railCamera_->OnCollision();
			player_->OnCollision();
		}
		for (int i = 0; i < 1; i++) {
			if (input_->TriggerKey(DIK_R))
			{

				pBoostUse = false;
				spManager->EnemyDead();
				player_->resetStage();
				
				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				overTimer = 1500;
				//bullet->OnCollision();
				//isRestart_ = true;
				break;
			}

			if (isRestart_ == true) {
				
				isStart_ = false;
				scene = 1;
				isRestart_ = false;
				break;
			}
		}

		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		CheckAllCollisions();
		viewProjection_.TransferMatrix();
		if (player_->nexxtStage()) 
		{

			scene += 1;
			railCamera_->Restart();
			
			for (int i = 0; i < 1; i++) {
				OverTimerReset();
				player_->resetStage();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				enemyManager->EnemyReset();
				//bullet->OnCollision();
				spManager->EnemyDead();
				pBoostUse = false;
				resetMusic = true;
			}

		}
		for (int i = 0; i < 1; i++) {
			if (resetMusic == true) {

				
				resetMusic = false;
				
			}
		}
	}
	if (scene == 2) {
		if (playerDead == false)
		{
			overTimer2--;
		}
		if (overTimer2 <= 0) {
			railCamera_->OnCollision();
			player_->OnCollision();
		}
		enemyManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		/*enemyManager->EventStart(audio_, SDManager);*/
		spManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		spManager->EventStart(audio_, SDManager);
		//自キャラの更新
		player_->Update();
		//敵の更新
		enemy_->Update();
		victory_->Update();
		railCamera_->Update();
		gManager.Update2();
		bManager.Update();
		pedestrianManager.Update2();
		windManager.Update();
		crossManager.Update();
		pyramidManager.Update();
		camelManager.Update();
		skydomee_->Update2();
		enemyManager->EventStart(audio_, SDManager);
		//player_->resetStage();
		
		victory_->Restart();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		CheckAllCollisions();
		viewProjection_.TransferMatrix();
		if (player_->nexxtStage() == true) {
			scene += 1;
			railCamera_->Restart();
			for (int i = 0; i < 1; i++) {
				player_->resetStage();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				enemyManager->EnemyReset();
				//bullet->OnCollision();
				spManager->EnemyDead();
				pBoostUse = false;
				overTimer2 = 2000;
			}
		}
		for (int i = 0; i < 1; i++) {
			if (input_->TriggerKey(DIK_R))
			{
				pBoostUse = false;
				//enemyManager->EnemyDead();
				enemyManager->EnemyReset();
				player_->resetStage();
				overTimer2 = 2000;
				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				spManager->EnemyDead();
				//bullet->OnCollision();
				isRestart_ = true;
				break;
			}

			if (isRestart_ == true) {
				isStart_ = false;
				scene = 2;
				isRestart_ = false;
				break;
			}
		}
	}
	if (scene == 3) {
		if (playerDead == false)
		{
			overTimer3--;
		}
		if (overTimer3 <= 0) {
			railCamera_->OnCollision();
			player_->OnCollision();
		}
		//自キャラの更新
		player_->Update();
		//敵の更新
		enemy_->Update();
		victory_->Update();
		railCamera_->Update();
		gManager.Update3();
		bManager.Update();
		//pedestrianManager.Update2();
		crossManager.Update();
		//pyramidManager.Update();
		//camelManager.Update();
		skydomeee_->Update2();
		/*enemyManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		enemyManager->EventStart(audio_, SDManager);*/

		asteroidManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		asteroidManager->EventStart(audio_, SDManager);

		spManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		spManager->EventStart(audio_, SDManager);

		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		CheckAllCollisions();
		viewProjection_.TransferMatrix();
		if (player_->nexxtStage() == true) {
			scene += 1;
			railCamera_->Restart();
			for (int i = 0; i < 1; i++) {
				//asteroidManager->EnemyReset();
				player_->resetStage();
				overTimer3 = 1500;
				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				asteroidManager->EnemyDead();
				spManager->EnemyDead();
				pBoostUse = false;
				overTimer3 = 1500;
				//bullet->OnCollision();

			}
		}
		for (int i = 0; i < 1; i++) {
			if (input_->TriggerKey(DIK_R))
			{
				player_->resetStage();
				overTimer3 = 1500;
				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				//asteroidManager->EnemyReset();
				asteroidManager->EnemyDead();
				spManager->EnemyDead();
				//bullet->OnCollision();
				isRestart_ = true;
				pBoostUse = false;
				break;
			}

			if (isRestart_ == true) {
				isStart_ = false;
				scene = 3;
				isRestart_ = false;
				break;
			}
		}
	}
	if (scene == 4) {

		//自キャラの更新
		player_->Update();
		player_->OnCollision();
		//敵の更新
		enemy_->Update();
		victory_->Update();
		railCamera_->Update();
		railCamera_->OnCollision();
		gManager.Update3();
		bManager.Update();
		//pedestrianManager.Update2();
		crossManager.Update();
		//pyramidManager.Update();
		//camelManager.Update();
		skydomeee_->Update2();
		/*enemyManager->Update(player_->GetWorldPosition(), bManager.IsBossBattle(), audio_, SDManager);
		enemyManager->EventStart(audio_, SDManager);*/

		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		CheckAllCollisions();
		viewProjection_.TransferMatrix();
		if (player_->nexxtStage() == true) {
			scene += 1;
			railCamera_->Restart();
			for (int i = 0; i < 1; i++) {
				//asteroidManager->EnemyReset();
				player_->resetStage();

				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				asteroidManager->EnemyDead();
				spManager->EnemyDead();
				pBoostUse = false;
				//bullet->OnCollision();

			}
		}
		for (int i = 0; i < 1; i++) {
			if (input_->TriggerKey(DIK_R))
			{
				player_->resetStage();

				victory_->Restart();
				player_->Reset();
				enemy_->Reset();
				railCamera_->Restart();
				//asteroidManager->EnemyReset();
				asteroidManager->EnemyDead();
				spManager->EnemyDead();
				//bullet->OnCollision();
				isRestart_ = true;
				pBoostUse = false;
				break;
			}

			if (isRestart_ == true) {
				isStart_ = false;
				scene = 4;
				isRestart_ = false;
				break;
			}
		}
	}

	if (player_->nexxtStage() == true) {

		scene += 1;
		railCamera_->Restart();
		for (int i = 0; i < 1; i++) {
			spManager->EnemyDead();
			player_->resetStage();
			
			victory_->Restart();
			player_->Reset();
			enemy_->Reset();
			railCamera_->Restart();
			pBoostUse = false;
			//bullet->OnCollision();

		}
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	if (scene == -1) {
		title.BackDraw();
	}
	if (scene == 0 || scene == 4) {
		title.BackDraw();
	}

	// スプライト描画後処理

	Sprite::PostDraw();

	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();

#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	
	/// </summary>
	//3Dモデル描画
	
	if (/*isStart_ == true*/scene == 1) {
		skydome_->Draw(viewProjection_);
		victory_->Draw(viewProjection_);
		spriteTimer->SetSize({ 0.0f + overTimer, 100.0f * 1.3f });
		
		//自機の描画
		crossManager.Draw(viewProjection_);
		signalManager.Draw(viewProjection_);
		gManager.Draw(viewProjection_);
		player_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);
		player_->SpriteDraw();

		bManager.Draw(viewProjection_);
		if(playerDead==false){
		pedestrianManager.Draw(viewProjection_);
		}
		if(player_->IsSpeed())
		{
		audio_->PlayWave(carFX, false, 0.03f);
		//audio_->PlayWave(selectFX, false, 0.008f);
		spManager->Draw(viewProjection_);
		}
	}

	if (/*isStart_ == true*/scene == 2) {
		spriteTimer->SetSize({ 0.0f + overTimer2, 100.0f * 1.3f });
		skydomee_->Draw(viewProjection_);
		pyramidManager.Draw(viewProjection_);
		camelManager.Draw(viewProjection_);
		//crossManager.Draw(viewProjection_);
		//signalManager.Draw(viewProjection_);
		gManager.Draw(viewProjection_);
		player_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);
		enemyManager->Draw(viewProjection_);
		//bManager.Draw(viewProjection_);
		//pedestrianManager.Draw(viewProjection_);
		windManager.Draw(viewProjection_);
	
		//自機の描画
		if (player_->IsSpeed())
		{
			audio_->PlayWave(carFX, false, 0.03f);
			//audio_->PlayWave(selectFX, false, 0.1f);
			spManager->Draw(viewProjection_);
		}
	}
	if (/*isStart_ == true*/scene == 3) {
		skydomeee_->Draw(viewProjection_);
		//crossManager.Draw(viewProjection_);
		//signalManager.Draw(viewProjection_);
		gManager.Draw(viewProjection_);
		player_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);
		//bManager.Draw(viewProjection_);
		
		//自機の描画
		//enemyManager->Draw(viewProjection_);
		asteroidManager->Draw(viewProjection_);
		if (player_->IsSpeed())
		{
			audio_->PlayWave(carFX, false, 0.03f);
			//audio_->PlayWave(selectFX, false, 0.1f);
			spManager->Draw(viewProjection_);
		}
	}
	if(scene == -1)
	{
	toManager->Draw(viewProjection_);
	to2Manager->Draw(viewProjection_);
	to3Manager->Draw(viewProjection_);
	
	//spManager->Draw(viewProjection_);
	//player_->Draw(viewProjection_);
	title.ModelDraw(titleView);
	}
	if (scene == 0 || scene == 4)
	{
		toManager->Draw(viewProjection_);
		to2Manager->Draw(viewProjection_);
		to3Manager->Draw(viewProjection_);

		//spManager->Draw(viewProjection_);
		//player_->Draw(viewProjection_);
		title.ModelDraw(titleView);
	}
	if (scene == 4)
	{
		toManager->Draw(viewProjection_);
		to2Manager->Draw(viewProjection_);
		to3Manager->Draw(viewProjection_);
		//title.WinDraw();
		//player_->Draw(viewProjection_);

	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	 
	if (scene == -1 /*|| scene == 4*/) {
		title.TitleFrontDraw();
		player_->Reset();
	}
	if (scene == 0) {
		title.FrontSetsumeiDraw();
	}

	if (scene == 4)
	{
		title.WinDraw();
		
	}
	if (/*isStart_ == true*/scene == 1) {
		title.FrontDraw();
		if (pBoostUse == false) {
			title.BoostX1Draw();
		}
		else if (pBoostUse == true) {
			title.BoostX0Draw();
		}
	}
	if (/*isStart_ == true*/scene == 2) {
		title.FrontDraw();
		if (pBoostUse == false) {
			title.BoostX1Draw();
		}
		else if (pBoostUse == true) {
			title.BoostX0Draw();
		}
	}
	if (/*isStart_ == true*/scene == 3) {
		spriteTimer->SetSize({ 0.0f + overTimer3, 100.0f * 1.3f });
		title.FrontDraw();
		if (pBoostUse == false) {
			title.BoostX1Draw();
		}
		else if (pBoostUse == true) {
			title.BoostX0Draw();
		}
	}
	if (overTimer < 0 && player_->IsDead() && scene == 1) {
		title.TimeUpDraw();
	}

	if (overTimer > 0 && scene == 1) {
	spriteTimer->Draw();
	title.SpriteTimerText();
	}

	if (overTimer2 < 0 && player_->IsDead() && scene == 2) {
		title.TimeUpDraw();
	}

	if (overTimer2 > 0 && scene == 2) {
		spriteTimer->Draw();
		title.SpriteTimerText();
	}
	if (overTimer3 < 0 && player_->IsDead() && scene == 3) {
		title.TimeUpDraw();
	}

	if (overTimer3 > 0 && scene == 3) {
		spriteTimer->Draw();
		title.SpriteTimerText();
	}
	if (playerDead == true && player_->IsDead()) {
		title.GameOverDraw();
	}
	if (player_->IsGoal())
	{
		pBoostUse = false;
	}
	if (input_->PushKey(DIK_E))
	{
		pBoostUse = true;
	}
	if (input_->PushKey(DIK_R))
	{
		pBoostUse = false;
		playerDead = false;
	}
	debugText_->SetPos(50, 310);
	debugText_->SetScale(0);
	debugText_->Printf("TIME UP:(%d)", overTimer);
	debugText_->SetPos(50, 330);
	debugText_->Printf("TIME UP:(%d)", overTimer2);
	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}


void GameScene::CheckAllCollisions()
{
	// 判定対象AとBの座標
	Vector3 posA, posB;
	// 半径AとBの距離の計算
	float posAR = 1.0f;
	float posBR = 1.0f;

	// 自弾リストの取得
	const std::list < std::unique_ptr<PlayerBullet>>& playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list < std::unique_ptr<EnemyBullet>>& enemyBullets = enemy_->GetBullets();
	const std::list < std::unique_ptr<Enemy2>>& enemy = enemyManager->enemys;
	const std::list < std::unique_ptr<Asteroid>>& enemy2 = asteroidManager->enemys;
	//const std::list < std::unique_ptr<Asteroid>>& asteroid2 = asteroidManager->asteroids;
#pragma region 自キャラとOBAの当たり判定
	if (scene == 1) {
		// 自キャラの座標
		posA = player_->GetWorldPosition();
	
		// 自キャラとOBAの当たり判定
		/*for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {*/
		for (const std::unique_ptr<Pedestrian>& pedestrian : pedestrianManager.GetObjects())
		{
			posB = pedestrian->GetWorldPosition();
			// 敵弾の座標
			/*posB = bullet->GetWorldPosition();*/

			// 座標AとBの距離を求める
			float dx = posB.x - posA.x;
			float dy = posB.y - posA.y;
			float dz = posB.z - posA.z;

			float radius = (posAR + posBR) * (posAR + posBR);

			// 球と球の交差判定
			if ((dx * dx) + (dy * dy) + (dz * dz - 10) <= radius + 8) {
				// 自キャラの衝突時コールバックを呼び出す
				//player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				pedestrian->OnCollision();
				audio_->PlayWave(hitFX, false, 0.3f);
				//enemy_->OnCollision();
				victory_->OnCollision();
				railCamera_->OnCollision();
				player_->OnCollision();
				playerDead = true;
			}
			

			if (player_->nexxtStage() == true) {
				scene += 1;
				railCamera_->Restart();
				for (int i = 0; i < 1; i++) {
					playerDead = false;
					player_->resetStage();
					
					victory_->Restart();
					player_->Reset();
					enemy_->Reset();
					railCamera_->Restart();
					pedestrian->Reset();
					//bullet->OnCollision();

				}
			}

			if (input_->TriggerKey(DIK_R))
			{
				pedestrian->Reset();
				playerDead = false;
			}
			if (input_->TriggerKey(DIK_T))
			{
				pedestrian->Reset();
				/*playerDead = false;*/
			}
		}
	}
#pragma endregion

	if (scene == 2) {
#pragma region 自キャラとCAMELの当たり判定

		// 自キャラの座標
		posA = player_->GetWorldPosition();

		// 自キャラとOBAの当たり判定
		/*for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {*/
		for (const std::unique_ptr<Enemy2>& camel : enemyManager->enemys)
		{
			posB = camel->GetWorldPosition();
			// 敵弾の座標
			/*posB = bullet->GetWorldPosition();*/

			// 座標AとBの距離を求める
			float dx = posB.x - posA.x;
			float dy = posB.y - posA.y;
			float dz = posB.z - posA.z;

			float radius = (posAR + posBR) * (posAR + posBR);

			// 球と球の交差判定
			if ((dx * dx) + (dy * dy) + (dz * dz - 8) <= radius + 8) {
				// 自キャラの衝突時コールバックを呼び出す
				//player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				camel->OnCollision();
				audio_->PlayWave(hitFX, false, 0.3f);
				//enemy_->OnCollision();
				victory_->OnCollision();
				railCamera_->OnCollision();
				player_->OnCollision();
				playerDead = true;
			}
			/*debugText_->SetPos(50, 10);
			debugText_->Printf("posB:(%f,%f,%f)", posB.x, dy * dy, posB.z);
			debugText_->SetPos(100, 10);
			debugText_->Printf("radius:(%f)", radius);*/

			if (player_->nexxtStage() == true) {
				scene += 1;
				railCamera_->Restart();
				for (int i = 0; i < 1; i++) {
					playerDead = false;
					player_->resetStage();
				
					victory_->Restart();
					player_->Reset();
					enemy_->Reset();
					railCamera_->Restart();
					//camel->Reset();
					//bullet->OnCollision();

				}
			}

			if (input_->TriggerKey(DIK_R))
			{
				playerDead = false;
			}
		}

#pragma endregion

#pragma region 自キャラとWINDの当たり判定

		// 自キャラの座標
		posA = player_->GetWorldPosition();

		// 自キャラとOBAの当たり判定
		/*for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {*/
		for (const std::unique_ptr<WindObj>& wind : windManager.GetObjects())
		{
			posB = wind->GetWorldPosition();
			// 敵弾の座標
			/*posB = bullet->GetWorldPosition();*/

			// 座標AとBの距離を求める
			float dx = posB.x - posA.x;
			float dy = posB.y - posA.y;
			float dz = posB.z - posA.z;

			float radius = (posAR + posBR) * (posAR + posBR);

			// 球と球の交差判定
			if ((dx * dx) + (dy * dy) + (dz * dz) <= radius + 500) {
				// 自キャラの衝突時コールバックを呼び出す
				//player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				//wind->OnCollision();
				player_->WindCollision();
				railCamera_->WindCollision();
				//enemyManager->EnemyPop();
			}

			if (player_->nexxtStage() == true) {
				scene += 1;
				railCamera_->Restart();
				for (int i = 0; i < 1; i++) {

					player_->resetStage();
				
					victory_->Restart();
					player_->Reset();
					enemy_->Reset();
					railCamera_->Restart();
					wind->Reset();
					//bullet->OnCollision();

				}
			}

			if (input_->TriggerKey(DIK_R))
			{
				wind->Reset();
			}
			if (input_->TriggerKey(DIK_T))
			{
				//wind->Reset();
			}
		}

#pragma endregion
	}
	if (scene == 3) {
#pragma region 自キャラとCAMELの当たり判定

		// 自キャラの座標
		posA = player_->GetWorldPosition();

		// 自キャラとOBAの当たり判定
		/*for (const std::unique_ptr<EnemyBullet>& bullet : enemyBullets) {*/
		for (const std::unique_ptr<Asteroid>& camel : asteroidManager->enemys)
		{
			posB = camel->GetWorldPosition();
			// 敵弾の座標
			/*posB = bullet->GetWorldPosition();*/

			// 座標AとBの距離を求める
			float dx = posB.x - posA.x;
			float dy = posB.y - posA.y;
			float dz = posB.z - posA.z;

			float radius = (posAR + posBR) * (posAR + posBR);

			// 球と球の交差判定
			if ((dx * dx) + (dy * dy) + (dz * dz) <= radius + 30) {
				// 自キャラの衝突時コールバックを呼び出す
				//player_->OnCollision();
				// 敵弾の衝突時コールバックを呼び出す
				camel->OnCollision();
				audio_->PlayWave(hitFX, false, 0.3f);
				//enemy_->OnCollision();
				victory_->OnCollision();
				railCamera_->OnCollision();
				player_->OnCollision();
				playerDead = true;
			}
		/*	debugText_->SetPos(50, 240);
			debugText_->Printf("posB:(%f,%f,%f)", posB.x, dx * dx, posB.z);
			debugText_->SetPos(100, 240);
			debugText_->Printf("radius:(%f)", radius);*/

			if (player_->nexxtStage() == true) {
				scene += 1;
				railCamera_->Restart();
				for (int i = 0; i < 1; i++) {

					player_->resetStage();
					
					victory_->Restart();
					player_->Reset();
					enemy_->Reset();
					railCamera_->Restart();
					//camel->Reset();
					//bullet->OnCollision();

				}
			}

			if (input_->TriggerKey(DIK_R))
			{

			}
		}
	}
#pragma endregion
#pragma region 自キャラと敵キャラの当たり判定
	//	// 敵キャラの座標
	//	posA = enemy_->GetWorldPosition();
	//
	//		// 自弾の座標
	//		posB = player_->GetWorldPosition();
	//
	//		// 座標AとBの距離を求める
	//		float dx = posB.x - posA.x;
	//		float dy = posB.y+0.2 - posA.y;
	//		float dz = posB.z - posA.z;
	//
	//		float radius = (posAR + posBR) * (posAR + posBR);
	//
	//		// 球と球の交差判定
	//		if ((dx * dx) + (dy * dy) + (dz * dz) <= radius) {
	//			// 自キャラの衝突時コールバックを呼び出す
	//			
	//			enemy_->OnCollision();
	//			victory_->OnCollision();
	//			railCamera_->OnCollision();
	//			player_->OnCollision();
	//			// 敵弾の衝突時コールバックを呼び出す
	//
	//		}
	//		debugText_->SetPos(50, 10);
	//		debugText_->Printf("posB:(%f,%f,%f)",posB.x, dy * dy,posB.z);
	//		debugText_->SetPos(1000 , 10);
	//		debugText_->Printf("radius:(%f)", radius);
	//
#pragma endregion
#pragma region 自弾と敵弾の当たり判定
	//// 自弾と敵弾の当たり判定
	//for (const std::unique_ptr<PlayerBullet>& bulletA : playerBullets) {
	//	for (const std::unique_ptr<EnemyBullet>& bulletB : enemyBullets) {
	//		// 自弾の座標
	//		posA = bulletA->GetWorldPosition();
	//		// 敵弾の座標
	//		posB = bulletB->GetWorldPosition();

	//		// 座標AとBの距離を求める
	//		float dx = posB.x - posA.x;
	//		float dy = posB.y - posA.y;
	//		float dz = posB.z - posA.z;

	//		float distance = dx * dx + dy * dy + dz * dz;
	//		float radius = (posAR + posBR) * (posAR + posBR);

	//		// 球と球の交差判定
	//		if (distance <= radius) {
	//			// 自キャラの衝突時コールバックを呼び出す
	//			bulletB->OnCollision();
	//			// 敵弾の衝突時コールバックを呼び出す
	//			bulletA->OnCollision();
	//		}
	//	}
	//}

#pragma endregion
}
