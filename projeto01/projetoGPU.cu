#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/fill.h>
#include <thrust/copy.h>
#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;


struct functor 
{
   int mov_count;
   int n_cat;
   int *lim_cats;
   movie *movies;

   functor(int _mov_count, movie *_movies, int _n_cat ,int *_lim_cats) : mov_count(_mov_count), movies(_movies), n_cat(_n_cat) ,lim_cats(_lim_cats) {
      
   };
   __device__ __host__
   int operator() (int selection_it)
   {  

      bool slots[30];
      for(int h = 0; h < 30; h++) {
        slots[h] = false;
      }

      int lim_cats_cp[30];
      for(int h = 0; h <= n_cat; h++) {
        lim_cats_cp[h] = lim_cats[h];
      }

      int added = 0;
      for(int i = 0; i < mov_count; i++)
      {
          if(added > 24) return -1;
          if(selection_it & (1 << i))
          {
              if(movies[i].end == movies[i].start) {
                if(slots[movies[i].start]) return -1;
                slots[movies[i].start] = true;
              } 
              else {
                for(int j = movies[i].start; j < movies[i].end; j++) {
                  if(slots[j]) return -1;
                  slots[j] = true;
                }
              }
              //cout << movies[i].cat << endl;
              if(lim_cats_cp[movies[i].cat] == 0) return -1;
              lim_cats_cp[movies[i].cat] --;
              added++;
          }
      }
      return added;
   }
};

void test_combinations(vector<movie> &movies, vector<int> &lim_cats, int n_cat) {
  chrono::steady_clock::time_point begin = get_time();
  
  thrust::device_vector<int> cats_lim_gpu(lim_cats);
  //cats_lim_gpu = lim_cats;

  thrust::device_vector<movie> mov_gpu(movies);
  //mov_gpu = movies;

  thrust::device_vector<int> mov_count(pow(2, movies.size()));
  
  thrust::counting_iterator<int> comb(0);

  thrust::transform(comb, comb + pow(2, movies.size()), mov_count.begin(), functor(movies.size(), thrust::raw_pointer_cast(mov_gpu.data()), n_cat ,thrust::raw_pointer_cast(cats_lim_gpu.data())));
  int best = *thrust::max_element(mov_count.begin(), mov_count.end());

  chrono::steady_clock::time_point end = get_time();

  cout << get_interval(begin, end) << 'x' << pow(2, movies.size()) << 'x' << pow(2, movies.size());
}

int main(int argc, char *argv[]) {
  int n_mov, n_cat;

  vector<movie> movies, selected;
  vector<int> lim_cats;

  cin >> n_mov >> n_cat;
  
  movies.reserve(n_mov);

  read_cats_limit(lim_cats, n_cat);
  read_movies_data(movies, n_mov);

  test_combinations(movies, lim_cats, n_cat);

}