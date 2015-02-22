#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_vertex(int index, int kinect, float* vertices_x, float* vertices_y, float* vertices_z, int* vert_enabled, int* vert_map, int num_vertices, int* depth, float* cameras) {
    if (!vert_enabled[index]) {
     vert_enabled[index] = 1;
     float v_x, v_y, v_z;
     float img_x = (index % 512) - 212;
     float img_y = index / 512 - 256;
     float img_phi = img_y * (60.0/424.0);
     float img_theta = img_x * (70.0/512.0);
     float img_rho = depth[index];

     float cam_x = img_rho * (sin(img_phi)*cos(img_theta));
     float cam_y = img_rho * (sin(img_phi)*sin(img_theta));
     float cam_z = img_rho * (cos(img_phi));

     float x_off = cameras[kinect*i][0];
     float y_off = cameras[kinect*i][1];
     float z_off = cameras[kinect*i][2];

     float roll = cameras[kinect*i][3];
     float yaw = cameras[kinect*i][4];
     float pitch = cameras[kinect*i][5];

v_x = cam_x;
v_y = cam_y;
v_z = cam_z;

     cam_x = (cos(yaw)*v_x - sin(yaw)*v_z);
     cam_y = (v_y*(-sin(yaw)) + v_x*cos(yaw));
     
v_x = cam_x;
v_y = cam_y;

     cam_x = (v_x*cos(pitch) + v_z*sin(pitch));
     cam_z = (v_z*cos(pitch)-sin(pitch)*v_x);
    
v_x = cam_x;
v_z = cam_z;
 
     cam_y = cos(roll)*v_y - sin(roll)*v_z;
     cam_z = sin(roll)*y_y + cos(roll)*v_z;

v_x = cam_x;
v_y = cam_y;
v_z = cam_z;

     vertices_x[num_vertices] = v_x + offset[0];
     vertices_y[num_vertices] = v_y + offset[1];
     vertices_z[num_vertices] = v_z + offset[2];
     vert_map[index] = num_vertices;
     return 1;
    }
    return 0;
}

int[] getDepth(int index, int* depth) {
	FILE* image;
	if (index != 100) {
		image = fopen("/mnt/josneville/josneville/Pictures/Kinect1.bmp", "r");
	}
	if (image == NULL){
		printf("Oh don't worry about it");
		return 0;
	}
	int i;
	for (i = 0; i < 54; i++) getc(image);
	for (i = 0; i < 512*424; i++) {
		getc(image);
		depth = ((int)(getc(image))) << 8;
		depth += getc(image);
		getc(image);
	}
}

int main(int argc, char ** argv){
	int[] depth[512*424];
	int[] depth_m[512*424];

	float x_angular_pitch = 70.0;
	float y_angular_pitch = 60.0;
	float x_angular_density = 70.0/512.0;
	float y_angular_density = 60.0/424.0;

//params to adjust with config.ini
	float max_depth = 50.0;
	int edge_filter = 2;
        float cameras[4*6];
int ahh;
for (ahh = 0; ahh < 24; ahh++) {
cameras[ahh] = 0;
}
while (1) {
 for (int i = 0; i<4; i++) {
  getDepth(i, depth);
  for (int j = 0 ; j < 512; j++) {
   for (int k = 0; k < 424; k++) {
    if (depth[k*512 + j] > max_depth) {
     depth_m[k*512 + j] = 1;
    } else {
    if (j>2 && j<509 && k>2 && k<421) {
// eugh might be way too slow
     for (int j_off = -2; j_off <=2; j_off++) {
      for (int k_off = -2; k_off <=2; k_off++) {
       if (depth[(k+k_off)*512+j+j_off] > max_depth) {
        depth_m[k*512+j] = 1;
        break;
       }
      }
     }
    } else {
     depth_m[k*512+j] = 0;
    }
   }
  }

 int num_vertices = 0;
 int num_triangles = 0;
 float[] vertices_x[512*424];
 float[] vertices_y[512*424];
 float[] vertices_z[512*424];
 int[] triangle_1[2*512*424];
 int[] triangle_2[2*512*424];
 int[] triangle_3[2*512*424];
 int[] vert_enabled[512*424];
 int[] vert_map[512*424];

 for (int j = 1; j < 511; j++) {
  for (int k = 1; k < 423; k++) {
   if (!depth_m[k*512+j] && !depth_m[j-1+k*512] && !depth_m[(k-1)*512+j]) {
    num_vertices += check_vertex((k-1)*512+j, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    num_vertices += check_vertex(k*512+j, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    num_vertices += check_vertex(k*512+j-1, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    triangle_1[num_triangles] = vert_map[k*512+j];
    triangle_2[num_triangles] = vert_map[j-1+k*512];
    triangle_3[num_triangles] = vert_map[j+(k-1)*512];
    num_triangles++;
    
   }
   if (!depth_m[k*512+j] && !depth_m[j+1+k*512] && !depth_m[j+(k+1)*512]) {
    num_vertices += check_vertex((k+1)*512+j, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    num_vertices += check_vertex(k*512+j, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    num_vertices += check_vertex(k*512+j+1, i, vertices_x, vertices_y, vertices_z, vert_enabled, vert_map, num_vertices, depth, cameras);
    triangle_1[num_triangles] = vert_map[k*512+j];
    triangle_2[num_triangles] = vert_map[j+1+k*512];
    triangle_3[num_triangles] = vert_map[j+(k+1)*512];
    num_triangles++;

   }
  }
 }

 }

// getColor

// send mesh

}
return 0;
}

