#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
///<summary>
///�G
///</summary>
class Enemy{
public:
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	Enemy();

	///<summary>///������///</summary>///<paramname="model">���f��</param>///<paramname="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize();
	///<summary>
	///�X�V
	///</summary>
	void Update();
	///<summary>
	///�`��
	///</summary>
	//void Draw(ViewProjection viewProjection_);
	void Draw();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
};