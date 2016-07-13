

namespace TMatrix{
	typedef unsigned int size_t;

	template<typename T>
	class Matrix{
	public:

		//Matrix���m�̉��Z
		const Matrix operator +(Matrix m1, Matrix m2);
		const Matrix operator -(Matrix m1, Matrix m2);
		const Matrix operator *(Matrix m1, Matrix m2);

		//�X�J���[�Ƃ̉��Z
		template<typename scalar_t>
		const Matrix operator *(scalar_t scalar, Matrix m);

		//�s�񉉎Z
		Matrix Create_Trans_Mat(Matrix mat);
		Matrix Create_Inverse_Mat(Matrix mat);	//MEMO::LU����

		//------------------------------------------------------------------
		//MEMO::�ق�������
		//�E�x�N�g���ƍs����󂯎���āA�A��������������
		//------------------------------------------------------------------
	private:
		size_t ROW_SIZE;
		size_t COL_SIZE;
	};
}