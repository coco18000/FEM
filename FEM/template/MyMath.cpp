//-------------------------------------------------------
//@date		2016/07/08
//@author	KatsuyaKikuchi
//@brief	MyMath.hの実装
//-------------------------------------------------------

#include"MyMath.h"

namespace MyMath{


	const double rouding = 0.00001;
	//ガウスの消去法
	//完成してる
	std::vector<double> Gauss_Method(std::vector<double> vec, std::vector< std::vector<double> > mat){
		std::vector<double> ans_vec(vec.size(), 0);
		if (mat.size() != vec.size())return ans_vec;

		for (unsigned int i = 0; i < mat.size(); i++){
			mat[i].push_back(vec[i]);
		}
		
		
		for (unsigned int row = 0,col = 0; row < vec.size(); row++,col++){
			//最も大きいピボットを探す
			double max_pivot = abs(mat[row][col]);
			unsigned int max_index = row;
			for (unsigned int temp_row = row + 1; temp_row < vec.size(); temp_row++){
				if ( max_pivot < abs(mat[temp_row][col]) ){
					max_index = temp_row;
					max_pivot = abs(mat[temp_row][col]);
				}
			}
			//ピボットのための入れ替え
			std::vector<double> temp_vec = mat[max_index];
			mat[max_index] = mat[row];
			mat[row] = temp_vec;
			if (max_pivot < rouding) continue; //pivotが丸め誤差以下なら次の列へ
			
			max_pivot = mat[row][col];
			for (unsigned int i = col; i < mat[0].size(); i++){
				mat[row][i] /= max_pivot;
			}

			for (unsigned int temp_row = row + 1; temp_row < mat.size(); temp_row++){
				double pivot_num = mat[temp_row][col];
				for (int temp_col = col; temp_col < mat[temp_row].size(); temp_col++){
					mat[temp_row][temp_col] -= mat[row][temp_col] * pivot_num;
				}
			}
		}
		
		int col = 0, row = 0;
		for (auto _col : mat){
			for (auto _row : _col){
				//DrawFormatString(row * 105, col * 20, WHITE, "%f", _row);
				row++;
			}
			row = 0;
			col++;
		}
		
		for (int i = vec.size() - 1; i >= 0; i--){
			ans_vec[i] = mat[i][vec.size()];
			for (unsigned int j = i + 1; j < vec.size(); j++){
				ans_vec[i] -= ans_vec[j] * mat[i][j];
			}
		}
		return ans_vec;
	}
}