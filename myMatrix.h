template <typename T>
class MyMatrix {
private:
    std::unordered_map<std::pair<size_t, size_t>, T, std::hash<std::pair<size_t, size_t>>> data;  // Хеш-таблица для хранения элементов
    size_t rows, cols;

public:
    MyMatrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

    T get(size_t row, size_t col) const {
        auto it = data.find({row, col});
        if (it != data.end()) {
            return it->second;
        }
        return T(0);
    }

    void set(size_t row, size_t col, const T& value) {
        if (value == T(0)) {
            data.erase({row, col});
        } else {
            data[{row, col}] = value;
        }
    }

    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    void setSize(size_t _rows, size_t _cols){
        rows = _rows;
        cols = _cols;
    }
};

template <typename T>
MyMatrix<T>& transpose(MyMatrix<T>& mat) {
    mat.setSize(mat.getCols(), mat.getRows());
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            T saved = mat.get(j, i);
            mat.set(j,i,mat.get(i,j));
            mat.set(i,j,saved);
        }
    }
    return mat;
}

template <typename T>
MyVector<T>& add(const MyVector<T>& v1, MyVector<T>& v2) {
    size_t size = std::max(v1.getSize(), v2.getSize());
    v2.setSize(size);
    
    for (size_t i = 0; i < size; ++i) {
        v2.set(i, v1.get(i) + v2.get(i));
    }
    return v2;
}

template <typename T>
MyVector<T>& multiply(const MyMatrix<T>& mat, MyVector<T>& vec) {
    if (mat.getCols() != vec.getSize()) {
        throw std::invalid_argument("Matrix columns must match vector size");
    }

    vec.setSize(mat.getRows());

    for (size_t i = 0; i < mat.getRows(); ++i) {
        T sum = 0;
        for (size_t j = 0; j < mat.getCols(); ++j) {
            sum += mat.get(i, j) * vec.get(j);
        }
        vec.set(i, sum);
    }
    return vec;
}

template <typename T>
MyMatrix<T>& power(const MyMatrix<T>& mat, int exponent) {
    if (mat.getRows() != mat.getCols()) {
        throw std::invalid_argument("Matrix must be square for exponentiation");
    }
    
    MyMatrix<T> base = mat;
    while (exponent > 0) {
        mat = multiply(mat, mat);
        exponent -= 1;
    }
    return mat;
}

template <typename T>
MyVector<T> standardVectorAddition(const std::vector<T>& v1, std::vector<T>& v2) {
    size_t size = std::max(v1.size(), v2.size());
    MyVector<T> result(size);
    for (size_t i = 0; i < size; ++i) {
        result.set(i, (i < v1.size() ? v1[i] : 0) + (i < v2.size() ? v2[i] : 0));
    }
    return result;
}