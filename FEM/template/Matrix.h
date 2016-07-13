

namespace TMatrix{
	typedef unsigned int size_t;

	template<typename T>
	class Matrix{
	public:

		//Matrix同士の演算
		const Matrix operator +(Matrix m1, Matrix m2);
		const Matrix operator -(Matrix m1, Matrix m2);
		const Matrix operator *(Matrix m1, Matrix m2);

		//スカラーとの演算
		template<typename scalar_t>
		const Matrix operator *(scalar_t scalar, Matrix m);

		//行列演算
		Matrix Create_Trans_Mat(Matrix mat);
		Matrix Create_Inverse_Mat(Matrix mat);	//MEMO::LU分解

		//------------------------------------------------------------------
		//MEMO::ほしいもの
		//・ベクトルと行列を受け取って、連立方程式を解く
		//------------------------------------------------------------------
	private:
		size_t ROW_SIZE;
		size_t COL_SIZE;
	};
}