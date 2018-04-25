#include "stdafx.h"
#include"AImove.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"keiroK.h"
#include"Geizi.h"
#define REACH 5.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
#define PI 3.141592653589793 
AI NPC;
//今回はmを引用するNPCのハンドルとして、jを特殊部隊のハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_speed = 1000.0f; //ノーマル状態のときの移動速度。
}


AI::~AI()
{
}
bool AI::Start()
{
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	game=FindGO<Game>("Game");
	iNo = game->No++;
	m_position= game->pasu.m_pointList[game->da[iNo][0] - 1];
	m_position.y = 0.0f;
	m_skinModelData.Load(L"modelData/unityChan.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	m_charaCon.Init(
		20.0,			//半径。 
		100.0f,			//高さ。
		m_position		//初期位置。
	);
	game->siminUI[iNo]->kyorikeisan(game->da[iNo][1] - 1);
	SetTags(10);
	return true;
}
void AI::NPCNormal()
{

	CVector3 v = game->siminUI[iNo]->K - m_position;
	float len = v.Length();//長さ
	if (50 <= len) {
		//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
		m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), game->siminUI[iNo]->bekutor*m_speed);
	}
	else {
		if (ima >= 4)
			ima = 0;
		game->siminUI[iNo]->kyorikeisan(game->da[iNo][ima++] - 1);
	}
	CVector3 v2 = m_position - pl->m_position;
	float len1 = v2.Length();//長さ

	if (len1 < 500.0f) {//プレイヤーを見つけたら
		Gaizi->point += 0.1f;
		pa = Escape;
		retu_position = m_position;
		m_speed = 3000.0f;
		//DamageFlag = true;
		//プレイヤーから逃げる。
	}
	if (len1 < REACH) {//攻撃を受ける範囲まで近づいたら確実にダメージを受けるので
		pa = Damage;
		DamageFlag = true;//ダメージフラグをtrueにする。
	}
	//	/////////////////////////////////
	//	//一定のルートをうろうろする処理。
	//	/////////////////////////////////
	//
	//	FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//			AI* ai = (AI*)go;
	//			if (ai->Zonbe == 1) {                                        //それがゾンビだったら
	//				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
	//				if (kyori < 60.0f) {                                     //距離が視界範囲以内だったら
	//					float angle = VectorAngleDeg(ai->m_position);        //検索対象の座標を引数にする。
	//					if (angle <= 45.0f&&angle >= -45.0f) {                //角度が視界内だったら
	//																		  //ゾンビから逃げる。
	//						muki.x = m_forward.x*(-1);
	//						muki.y = m_forward.y*(-1);
	//						muki.z = m_forward.z*(-1);//反対の向きに向く。
	//						pa = Escape_NPC;
	//						NPCEscapeNumber = MyNumber;
	//						Chase_Zombie = ai;   //NPCからの逃走関数に使う。
	//					}
	//				}
	//			}
	//		}
	//
	//	});
	//	Player* pl = FindGO<Player>("Player");
	//	CVector3 v = m_position - pl->m_position;
	//	float len = v.Length();//長さ
	//	if (len < 60.0f) {//プレイヤーを見つけたら
	//		float angle = VectorAngleDeg(pl->m_position); //検索対象の座標を引数にする。
	//		if (angle <= 45.0f&&angle >= -45.0f) { //角度が視界内だったら
	//											   //プレイヤーから逃げる。
	//
	//			muki.x = m_forward.x*(-1);
	//			muki.y = m_forward.y*(-1);
	//			muki.z = m_forward.z*(-1);
	//			NPCEscapeNumber = MyNumber;
	//			pa = Escape_Player;
	//		}
	//	}
	//	//if (len < REACH) {//攻撃を受ける範囲まで近づいたら確実にダメージを受けるので
	//	//	DamageFlag = true;//ダメージフラグをtrueにする。
	//	//}
	//	//if (DamageFlag == true) {//プレイヤーからの攻撃を受けたら
	//	//	static int i = 0; //30フレームをカウントする。
	//	//	if (i >= 30) {
	//	//		pa = Damage;//30フレーム経過したらパターンをダメージに変える。
	//	//	}
	//	//	else {
	//	//		i++; //1フレーム経過をカウントする。
	//	//	}
	//	//	
	//	//}
}

void AI::NPCDamage()
{
	if (DamageFlag == true) {//プレイヤーからの攻撃を受けたら
		static int i = 0; //30フレームをカウントする。
		if (i >= 30) {
			//30フレーム経過したらゾンビ化。
			pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
			m_movespeed = { 0.5f, 0.0f, 0.0f }; //ゾンビノーマル状態のときの移動速度に変える。
			Zonbe = 1;
			DamageFlag = false;
		}
		else {
			i++; //1フレーム経過をカウントする。
		}
		
	}

}
//void AI::NPCEscape_NPC() //NPCからの逃走
//{
//	static bool LostFlag = false;  //見失ったかどうかを示すフラグ。
//								   ///////////////////
//								   //逃走に関する処理。
//								   ///////////////////
//
//	float len = GetKyori(this->m_position, Chase_Zombie->m_position);
//	if (len >= 60) { //距離が60以上空いたら
//		LostFlag = true;
//	}
//	if (LostFlag == true) { //見失ったら
//
//							/////////////////////
//							//元の位置に戻る処理。
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//元の位置の番号に戻ったら
//			pa = Normal; //パターンをノーマルに変える。
//			LostFlag = false;//フラグを元に戻す。
//		}
//
//	}
//}

//void AI::NPCEscape_Player() //プレイヤーからの逃走
//{
//	///////////////////
//	//逃走に関する処理。
//	///////////////////
//
//	static bool LostFlag = false;  //見失ったかどうかを示すフラグ。
//	Player* pl = FindGO<Player>("Player");
//	float len = GetKyori(this->m_position, pl->m_position);
//	if (len >= 120) { //距離が120以上空いたら
//		LostFlag = true; //NPCはプレイヤーを見失う。
//	}
//	if (LostFlag == true) { //見失ったら
//
//							/////////////////////
//							//元の位置に戻る処理。
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//元の位置の番号に戻ったら
//			pa = Normal; //パターンをノーマルに変える。
//			LostFlag = false;//フラグを元に戻す。
//		}
//
//	}
//}
void AI::NPCZombie_Normal()
{
	//一定範囲を徘徊する。

	//一定範囲内に他のNPCを見つけたら
	//float len;
	//if (len) {
	//	if (m->Zonbe == 0) {//それがゾンビではなかったら
	//		//視界内か、角度をとって調べる。

	//		if () {//角度内(視界内)だったら
	//			ZombieChaseNumber = MyNumber; //自分が立っていたパスの番号を記憶する。
	//			pa = Zombie_Chase; //パターンを追跡に変える。
	//		}
	//	}
	//}
	//この下あれ
	/////////////////////////////////
	//一定のルートをうろうろする処理。
	/////////////////////////////////
	//float min_Nagasa = 9999.0f;
	//FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//	if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//		AI* ai = (AI*)go;
	//		if (ai->Zonbe == 0) {   //それが一般市民だったら
	//			float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
	//			if (kyori < 60.0f) {  //距離が視界範囲以内だったら
	//				float angle = VectorAngleDeg(ai->m_position); //検索対象の座標を引数にする。
	//				if (angle <= 45.0f&&angle >= -45.0f) { //角度が視界内だったら
	//					if (kyori < min_Nagasa) { //自分に一番近いのなら
	//						min_Nagasa = kyori;
	//						Tansaku = ai;
	//					}
	//				}
	//			}
	//		}
	//	}

	//});

	//if (Tansaku != nullptr) {
	//	pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
	//}
}

void AI::NPCZombie_Chase()
{
	//float len = GetKyori(m_position, m->m_position);
	//if (len>80.0f||HitFlag == true) {//他のNPCを見失った(距離が80以上あいた)、あるいは攻撃を与えたら
	//	//元の位置に戻る。

	//	if (ZombieChaseNumber = MyNumber) {//元の位置の番号に戻ったら
	//		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
	//		HitFlag == false;
	//	}
	//}
		//else {
		//	/////////////////////////////////
		//	//市民NPCを追跡する処理。
		//	/////////////////////////////////
		//}
	//if (len<REACH) {//NPCに追いついたら
	//	//攻撃する(確実に当たる仕様)。

	//		HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
	//	}
	
}

void AI::NPCZombie_Attack()//vs特殊部隊
{
	//if (BattleFlag == false) {//部隊と戦っておらず、フリーな状態なら
	//	//一番近い部隊に移動する。
	//	float len = GetKyori(m_position,j->m_position );
	//	if (len<REACH) {//部隊に近づいたら
	//		BattleFlag == true;//戦闘を開始する。
	//	}
	//}

	if (BattleFlag == true) {//戦闘状態なら
     	 //部隊に攻撃する。
	}

	//if () {//部隊を倒したら
	//	//「戦闘を終了した」というフラグをたてる。
	//	BattleFlag = false;
	//}
	
}

float AI::GetKyori(CVector3 a, CVector3 b) //2つのオブジェクトの座標を受け取る。
{
	CVector3 v = a - b;
	float len = v.Length();//長さ
	return len;  //2つのオブジェクトの距離を返す。
}

void AI::Turn()//ここ
{
	if (fabsf(m_movespeed.x) < 0.001f
		&& fabsf(m_movespeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void AI::NPCRuet()//NPCルート
{

}

float AI::VectorAngleDeg(CVector3 c)
{
	
	CVector3 sa;
	m_forward;
	sa = c - m_position;

	sa.Normalize();//向きVectorにする。
	float kaku = acosf(m_forward.Dot(sa));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree = kaku * 180.0 / PI;

	return degree;
}
void AI::DamageHantei() //全てのゾンビと距離でダメージ判定をする。
{
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)go;
			if (ai->Zonbe == 1) {   //それがゾンビだったら
				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
				if (kyori < REACH) {  //距離が攻撃範囲以内だったら
					pa = Damage; //パターンをダメージにかえる。
				}
			}
		}
	});

	Player* pl = FindGO<Player>("Player");
	float kyori = GetKyori(this->m_position, pl->m_position);//自分との距離を求める。
	if (kyori < REACH) {  //距離が攻撃範囲以内だったら
		pa = Damage; //パターンをダメージにかえる。
	}
}
void AI::Update()
{
	//pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	
	if (ForceFlag==true) {//特殊部隊が出現したら
		pa = Zombie_Attack; //パターンをゾンビアタックに切り替える。
	}

	CQuaternion qBias;
	qBias = rotation(270);

	switch (pa) {
	case Normal:
		//NPCの動きを書く。
		NPCNormal();
		break;
	//case Escape_NPC:
	//	NPCEscape_NPC();
	//	break;
	//case Escape_Player:
	//	NPCEscape_Player();
	//	break;
	case Escape:
		NPCescape();
		break;
	case Return:
		NPCReturn();
		break;
	case Damage:
		NPCDamage();
		break;
	case Zombie_Normal:
		//NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//他のNPCを見つけた時の処理を書く。
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	default:
		NPCZombie_Normal();
		break;
	}

	if (Zonbe == 0) { //自分がゾンビではなかったら
		DamageHantei(); //ゾンビとの当たり判定をとる。
	}
	
	//Muve(m_movespeed);//ムーヴスピード入れると動く
	//m_movespeed.x += 0.001;
	// //qRot回転とキャラの回転を乗算して合成する。
	//qBias.Multiply(m_rotation, qBias);

	//NPCの前方向を計算

	//mRot.MakeRotationFromQuaternion(m_rotation);
	//m_forward.x = mRot.m[2][0];
	//m_forward.y = mRot.m[2][1];
	//m_forward.z = mRot.m[2][2];
	//m_forward.Normalize();
	//m_rite.x = mRot.m[0][0];
	//m_rite.y = mRot.m[0][1];
	//m_rite.z = mRot.m[0][2];
	//m_rite.Normalize();
	//m_position += m_forward *  m_speed;
	//m_position += m_rite * 10 * m_speed;		
	//CVector3 k = { 8881.04883
	//		,- 221.356491
	//		,9464.60547 };
	//	CVector3 b = {
	//		4190.29980
	//		,- 221.356491
	//		,4564.60596 };
	//	keiro=NewGO<keiroK>(0);

	//	keiro->tansa(k, b);
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::NPCReturn()
{
	int Size=keiro->jyunban.size();

	CVector3 v = game->siminUI[iNo]->K - m_position;
	float len = v.Length();//長さ
	if (50 <= len) {
		//m_position += game->siminUI[iNo]->bekutor*m_speed;
		m_position=	m_charaCon.Execute(GameTime().GetFrameDeltaTime(), (game->siminUI[iNo]->bekutor)*m_speed);
	}
	else {
		if (da >= Size) {
			ima--;
			pa = Normal;
			da = 1;
		}
		else {
			game->siminUI[iNo]->kyorikeisan(keiro->jyunban[da++] - 1);
			modori = 0;
		}
	}
}
void AI::NPCescape()
{

	CVector3 v = m_position - pl->m_position;
	float len = v.Length();//長さ
	if (len < 1000.0) {
		v.Normalize();//正規化して向きベクトルにする。
		v.y = 0.0f;
		//m_position += v * m_speed;
		m_position =m_charaCon.Execute(GameTime().GetFrameDeltaTime(),v*m_speed);
	}
	else {
		keiro = NewGO<keiroK>(0);
		keiro->tansa(m_position, retu_position);
		game->siminUI[iNo]->kyorikeisan(keiro->jyunban[0]-1);
		pa = Return;
		m_speed = 1000.0f;
	}
}

void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
