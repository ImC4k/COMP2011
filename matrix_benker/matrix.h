/*
 * 	This is a header file of matrix class which store the properties
 */

class matrix{

	private:
		int **arr;	//This store the value of matrix in integer type only
		int r-size;	//This store the size of matrix (row)
		int c-size;	//This store the size of matrix (col)
		int determinant; //This store the determinant of the matrix, determinant should be -1 indicate not initialized
	public:
		matrix();							//This is the default constructor of matrix object (nothing)
		matrix(int **p, int row, int col);	//This is a constructor of matrix object with a given array
		~matrix();							//This is a destructor
		bool setMatrix(int **p, int row, int col);				//This function is to replace the matrix
		bool replaceOne(int row, int col, int num);	//This function is to replace one cell in a matrix
		int setDeterminant();									//This function is to set determinant of the matrix		
	
		void printMatrix() const;	//This function print the matrix out		
};
