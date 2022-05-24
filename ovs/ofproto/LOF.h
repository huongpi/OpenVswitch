#ifndef __LOF_h__
#define __LOF_h__

#define DATANUM 600
#define K 10

/*tạo một struct kiểu neighbor chứa các thuộc tính của một điểm hàng xóm*/
typedef struct neighbor
{
    int index_list;          /*chỉ số của các điểm lân cận trong tập dữ liệu */
    float distance;          /*khoảng cách của điểm hàng xóm tới điểm đang xét */
}n_b;
/*tạo một struct kiểu data chứa các thuộc tính của một điểm dữ liệu*/
typedef struct data
{
    int index;                  /*chỉ số của điểm này trong tập dữ liệu*/
    float k_distance;           /*K_distance của điểm này*/
    n_b neighbor[DATANUM];      /*mảng chứa tập các điểm xung quanh điểm xét*/
    float traffic_norm;         /*lưu lượng của điểm xét ~ x */
    float n_flow_norm;          /*số flow mới của điểm xét ~ y*/
    /*2 thông tin chính để kiểm tra bất thường*/
     float lrd;               /* local reachability density của điểm hàng xóm của điểm xét  */
    float lof;                  /*lof(k) của điểm xét*/
}data_t;

//các phương thức tính toán
/*khoảng cách 2 điểm*/
float distance(data_t *a,data_t *b);

/*thuật toán sắp xếp bubble sort*/
void bubble_sort(data_t *a,int n);

/*hàm hoán đổi vị trí*/
void swap(n_b *a, n_b *b);

/*max*/
float max(float a, float b);

/*k_distance*/
float k_dis(data_t *a);

/*reachability distance*/
float reach_dis(data_t *a, data_t *b);

/*local reachability density của điểm xét với 1 điểm hàng xóm*/
void lrd_k(data_t *Arr[],int n);

/*tính lof*/
float LOF(data_t *a,data_t *Arr[],int n);

//chuẩn hóa dữ liệu
/*tính trung bình các điểm*/
float calc_mu(float *arr,int n);

/*tính độ lệch*/
float calc_sigma(float *arr,int n);

/*hàm tanh-estimators*/
float normalize(float x, float mu,float sigma);

/*tinh LOF cho qua trinh trainning*/
void LOF_training(data_t *Arr[],int n);
#endif
