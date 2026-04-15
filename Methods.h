using namespace std;

class Methods{
public:
    void NewtonInterpolationPolynomial(vector<vector<float>> Dots);
    void LagrangeInterpolationPolynomial(vector<vector<float>> Dots);
    void SmoothingPolynomials(vector<vector<float>> Dots, int a);
    vector<vector<float>> BuildMatrixKoeff(vector<vector<float>> Koeff, int a, vector<vector<float>> Dots);
    void FourDegreePolynomials();
    vector<float> GaussMethod(vector<vector<float>> Koeff);
    vector<float> MyDataForFourthDegree();
};
