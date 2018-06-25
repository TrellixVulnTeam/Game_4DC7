/*!
*@brief	�g�[���}�b�v�B
*/
#pragma once

namespace tkEngine {
	/*!
	*@brief	���m�N���[���t�B���^�[
	*/
	class CMonochromeFilter {
	public:
		CMonochromeFilter();
		~CMonochromeFilter();
		/*!
		*@brief	�쐬�B
		*/
		void Init(const SGraphicsConfig& config);

		/*!
		*@brief	���m�N���[���t�B���^�[�̃A���t�@�ݒ�
		*@param[in]	alpha �A���t�@�l(1.0�`0.0�̊Ԃ�1.0�ɋ߂��قǃ��m�N����������
		*/
		void SetAlpha(float alpha)
		{
			m_rate = alpha;
		}

		/*!
		*@brief	���m�N���[���t�B���^�[�̎��s�B
		*@param[in]	renderContext		�����_�����O�R���e�L�X�g
		*/
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);

	private:
		float			m_rate;
		CShader			m_vsShader;							//!<���_�V�F�[�_�[�B
		CShader			m_psShader;							//!<�ŏI�����V�F�[�_�[�B
		CConstantBuffer	m_cbRate;
		CShaderResourceView m_noiseTexture;
	};
}