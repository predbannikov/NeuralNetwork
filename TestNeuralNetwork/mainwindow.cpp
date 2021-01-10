#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iomanip>


using namespace std;
using namespace cv;

void printMat(Mat mat, int prec)
{
    cout << "[";
    for(int i=0; i<mat.size().height; i++)
    {
        if(i != 0)
            cout << " [";
        else
            cout << "[";
        for(int j=0; j<mat.size().width; j++)
        {
            cout << setprecision(prec) << fixed  << mat.at<double>(i,j);
            if(j != mat.size().width-1)
                cout << ", ";
            else {
                cout << "]" ;
                if(i+1 == mat.size().height)
                    cout << "]" << endl;
                else
                    cout << endl;
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);




    double i[3][1] = { {0.9},
                      {0.1},
                      {0.8}};


    double valW1[3][3] = {        // Рандомное значение весов W скрытого слоя
                              { 0.9, 0.3, 0.4},
                              { 0.2, 0.8, 0.2},
                              { 0.1, 0.5, 0.6}
                     };


    Mat input = Mat(cv::Size(1, 3), CV_64FC1, i);
    Mat weight1 = Mat(cv::Size(3, 3), CV_64FC1, valW1);
    printMat(input , 3);
//    printMat(weight1 , 3);
//    Mat X = weight1 * input;

//    printMat(X , 3);
//    cout << setprecision(3) << fixed << X << endl;


//    cout << matA << endl;
//    cout << matB << endl;
//    cout << matA * matB;

//    printMat(weight1, 3);

    cout << endl << "------------------------" << endl;

    interPython();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::interPython()
{


//    QGenericMatrix<5, 2, double> mat;

//    qDebug() << mat;



    PyStatus status;

        PyConfig config;
        PyConfig_InitPythonConfig(&config);

//        /* Set the program name. Implicitly preinitialize Python. */
//        status = PyConfig_SetString(&config, &config.program_name,
//                                    L"/path/to/my_program");
//        if (PyStatus_Exception(status)) {
//            qDebug() << "not set program name in config";
//            return 0;
//        }

//        status = Py_InitializeFromConfig(&config);
//        if (PyStatus_Exception(status)) {
//            qDebug() << "not set config";
//            return 0;
//        }
//        PyConfig_Clear(&config);


        /* Append our custom search path to sys.path */
//        QString curPath = QApplication::applicationDirPath();
//        std::wstring wstr = curPath.toStdWString();
////        std::cout << wstr.c_str() << std::endl;
//        status = PyWideStringList_Append(&config.module_search_paths, L"/path/to/my_executable");

////        std::cout << config.module_search_paths.items << std::endl;
//        if (PyStatus_Exception(status)) {
//            qDebug() << "not adding custom search path to sys.path";
//            return 0;
//        }

//        /* Override executable computed by PyConfig_Read() */
//        status = PyConfig_SetString(&config, &config.executable, L"/path/to/my_executable");
//        if (PyStatus_Exception(status)) {
//            qDebug() << "not adding custom search path to sys.path";
//            return 0;
//        }



    int result = EXIT_FAILURE;


//    std::cout << argv[0] << std::endl;
//    QApplication::arguments()[0].toStdWString().c_str();

    wchar_t *program = Py_DecodeLocale(QApplication::arguments()[0].toStdString().c_str(), NULL);
//    std::wcout << L">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << program << std::endl;
    Py_SetProgramName(program);
//    setenv("PYTHONPATH", ".", 0);
    PyConfig_Read(&config);

//    for(int i = 0; i < config.module_search_paths.length; i++) {
//        std::wcout << config.module_search_paths.items[i] << std::endl;
//    }


    Py_Initialize();

    PyObject* sys = NULL;
    PyObject* sys_path = NULL;
    PyObject* folder_path = NULL;




//    sys = PyImport_ImportModule("sys");
//    if (!sys) {
//        qDebug() << "sys not loaded";
//        return 0;
//    }
//    sys_path = PyObject_GetAttrString(sys, "path");
//    // Путь до наших исходников Python
//    folder_path = PyUnicode_FromString((const char*) ".");
//    PyList_Append(sys_path, folder_path);




    import_array();


//    PyRun_SimpleString("import numpy as np          \n"
//                       "import sys                  \n"
//                       "import os                   \n"
//                       "import test                   \n"
//                       "sys.path.append(os.getcwd())\n"
////                       "import mymodule             \n"
//                       "print (os.getcwd() )        \n"
//                       "print (test.func1())        \n"
////                       "test.myrun([1, 0, 0])        \n"
//                       "print (sys.argv[0])         \n"
//                       "print (a)                   \n");



    // Build the 2D array in C++
    const int SIZE = 3;
    npy_intp dims[2]{SIZE, SIZE};

    long double* c_out;
    const int ND = 2;
    long double(*c_arr)[SIZE]{ new long double[SIZE][SIZE] };
    if (!c_arr) {
        std::cerr << "Out of memory." << std::endl;
        return 0;
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            c_arr[i][j] = i  + j;

    // Convert it to a NumPy array.
    PyObject *pArray = PyArray_SimpleNewFromData( ND, dims, NPY_LONGDOUBLE, reinterpret_cast<void*>(c_arr));
    if (!pArray)
        goto fail_np_array;
    PyArrayObject *np_arr = reinterpret_cast<PyArrayObject*>(pArray);



    const char *module_name = "testt";
    PyObject *pName = PyUnicode_FromString(module_name);
    if (!pName)
        goto fail_name;
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (!pModule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module '%s'\n", module_name);
        goto fail_import;
    }


    const char *func_name = "myrun";
    PyObject *pFunc = nullptr;
    pFunc = PyObject_GetAttrString(pModule, func_name);
    if (!pFunc) {
        fprintf(stderr, "Error: could not import func '%s'\n", func_name);
        PyErr_Print();
        goto fail_getattr;
    }
    if (!PyCallable_Check(pFunc)){
        std::cerr << module_name << "." << func_name << " is not callable." << std::endl;
        goto fail_callable;
    }


    PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, pArray, NULL);
    if (!pReturn)
        goto fail_call;
    if (!PyArray_Check(pReturn)) {
        std::cerr << module_name << "." << func_name
                  << " did not return an array." << std::endl;
        goto fail_array_check;
    }
    PyArrayObject *np_ret = reinterpret_cast<PyArrayObject*>(pReturn);
    if (PyArray_NDIM(np_ret) != ND - 1) {
//        int len = PyArray_SHAPE(np_ret)[0];
        Mat m(3, 3, CV_64FC1, reinterpret_cast<long double*>(PyArray_DATA(np_ret)));
        printMat(m, 3);
        qDebug() << "#->|" << PyArray_SHAPE(np_ret)[0] << reinterpret_cast<long double*>(PyArray_DATA(np_ret));
        int len = PyArray_SHAPE(np_ret)[0];
        c_out = reinterpret_cast<long double*>(PyArray_DATA(np_ret));



        std::cout << "Printing output array" << std::endl;
        for (int i = 0; i < len * 3; i++)
            std::cout << c_out[i] << ' ';


        std::cerr << std::endl << module_name << "." << func_name << " returned array with wrong dimension. Currnet dim=" << PyArray_NDIM(np_ret) + 1 << std::endl;
        goto fail_ndim;
    }

    // Convert back to C++ array and print.
    int len = PyArray_SHAPE(np_ret)[0];
    c_out = reinterpret_cast<long double*>(PyArray_DATA(np_ret));
    std::cout << "Printing output array" << std::endl;
    for (int i = 0; i < len; i++)
        std::cout << c_out[i] << ' ';
    std::cout << std::endl;
    result = EXIT_SUCCESS;

fail_ndim:
fail_array_check:
    Py_DECREF(pReturn);
fail_call:
fail_callable:
    Py_DECREF(pFunc);
fail_getattr:
    Py_DECREF(pModule);
fail_import:
fail_name:
    Py_DECREF(pArray);
fail_np_array:
    delete[] c_arr;
fail_c_array:
    PyErr_Print();

    Py_Finalize();
    return 0;
}
