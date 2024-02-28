#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

int g_rows, g_columns;

double** create_random_matrix(int rows, int columns)
{
    // Create array[rows] of pointers
    double **matrix = new  double* [rows];

    srand(time(NULL));

    for(int i = 0; i < rows; i++)
    {
        // For each pointer create array[columns]
        matrix[i] = new double[columns];

        // Fill matrix with random numbers
        for(int j = 0; j < columns; j++)
            matrix[i][j] = rand() % 101 - 50;
    }

    return matrix;
}

double** create_user_matrix(int rows, int columns)
{
    // Create array[rows] of pointers
    double **matrix = new double* [rows];

    for(int i = 0; i < rows; i++)
    {
        // For each pointer create array[columns]
        matrix[i] = new double[columns];

        // Make user to fill matrix up
        cout << "Enter row #" << i + 1<< endl;
        for(int j = 0; j < columns; j++)
            cin >> matrix[i][j];
    }

    return matrix;

}

void show_matrix(double* matrix[], int rows, int columns)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
            cout << setw(6) << matrix[i][j];

        cout << endl;
    }
}

double** get_minor(double* matrix[], int rows, int columns, int r, int c)
{
    // Create matrix smaller by 1 row and 1 columns than given
    double **minor = create_random_matrix(rows - 1, columns - 1);

    // Traverse from first row to las in minor
    for(int minor_i = 0, mat_i = 0; minor_i < rows - 1; minor_i++, mat_i++)
    {
        // If mat_i of given matrix same as index of element skip iteration and decrease minor_i by 1
        // So loop doesn't run out of minor
        if(mat_i == r)
        {
            minor_i--;
            continue;
        }

        //Traverse from first column to lat in minor
        for(int minor_j = 0, mat_j = 0; minor_j < columns - 1; minor_j++, mat_j++)
        {
            // If mat_j of given matrix same as index of element skip iteration and decrease minor_j by 1
            // So loop doesn't run out of minor
            if(mat_j == c)
            {
                minor_j--;
                continue;
            }

            // Copy all elemens of given matrix to minor exept ones that crossed out
            minor[minor_i][minor_j] = matrix[mat_i][mat_j];
        }
    }

    return minor;
}

double det(double * matrix[], int rows, int columns)
{
    double m_det = 0, elem, minor_det;
    char *formula = new char[200]{};
    char buff[20]{};

    if(rows != columns)
        return 0;

    // If only one element has left return it
    if(rows == 1 && columns == 1)
        return matrix[0][0];

    // Traverse first row from first to last element
    for(int i = 0; i < columns; i++)
    {
        // Save copy of element
        elem = matrix[0][i];

        // sum m_det with (-1)^(i + j)*saved element*minor of saved elemet
        minor_det = det(get_minor(matrix, rows, columns, 0, i), rows - 1, columns - 1);
        m_det += pow(-1, i)*elem*minor_det;

        if(rows == g_rows && columns == g_columns)
        {
            snprintf(buff, 20, "%.2f*%.2f*", elem, minor_det*pow(-1, i));
            strcat(formula, buff);
        }
    }

    if(g_rows == rows && g_columns == columns)
    {
        formula[strlen(formula) - 1] = '\0';
        cout << formula << " = ";
    }

    return m_det;
}

void display_menu()
{
    cout << "Choose from options below\n";
    cout << "1: Calculate det for random matrix\n";
    cout << "2: Calculate det for user matrix\n";
    cout << "3: Exit\n";
    cout << "Your choise: ";
}

int main()
{
    double **mat;
    double matrix_det;
    int choise;

    while(choise != 3)
    {
        display_menu();
        cin >> choise;

        switch(choise)
        {
            case 1:
                cout << "Enter rows and columns number: ";
                cin >> g_rows >> g_columns;

                mat = create_random_matrix(g_rows, g_columns);
                show_matrix(mat, g_rows, g_columns);

                matrix_det = det(mat, g_rows, g_columns);
                cout << matrix_det << "\n\n";
                break;
            case 2:
                cout << "Enter rows and columns number: ";
                cin >> g_rows >> g_columns;

                mat = create_user_matrix(g_rows, g_columns);
                show_matrix(mat, g_rows, g_columns);

                matrix_det = det(mat, g_rows, g_columns);
                cout << matrix_det << "\n\n";
                break;
        }
    }

}