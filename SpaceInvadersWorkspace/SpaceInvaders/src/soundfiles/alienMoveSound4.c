#include <stdint.h>

int32_t alienMoveSound4_sampleRate = 11025;
int32_t alienMoveSound4_numSamples = 1098;

int32_t alienMoveSound4_soundData[] = {
133, 133, 128, 133, 128, 128, 133, 133, 139, 133, 128, 133, 133, 133, 133,
133, 128, 133, 133, 128, 133, 128, 133, 133, 133, 122, 99, 77, 54, 31,
20, 9, 15, 26, 43, 60, 88, 99, 128, 139, 161, 184, 201, 218, 229,
240, 246, 255, 255, 255, 255, 255, 255, 255, 255, 252, 252, 240, 235, 224,
218, 207, 201, 190, 184, 167, 156, 150, 133, 128, 122, 116, 105, 99, 82,
82, 71, 71, 60, 60, 60, 71, 82, 94, 88, 94, 99, 88, 82, 65,
54, 43, 31, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 15, 26, 37,
54, 60, 77, 82, 99, 111, 122, 128, 139, 150, 167, 173, 190, 201, 212,
218, 229, 235, 246, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 246, 235, 229, 224,
224, 212, 201, 195, 184, 161, 133, 111, 82, 60, 43, 37, 31, 37, 43,
54, 65, 82, 94, 105, 116, 122, 133, 139, 144, 150, 161, 161, 161, 167,
161, 156, 150, 150, 144, 139, 128, 128, 122, 116, 105, 99, 82, 77, 65,
54, 43, 37, 26, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 26, 43, 60, 77, 94,
111, 128, 139, 156, 173, 178, 195, 212, 224, 240, 252, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252, 235,
207, 178, 150, 128, 111, 99, 99, 105, 111, 122, 128, 139, 150, 167, 178,
190, 201, 201, 212, 218, 224, 224, 229, 224, 224, 224, 212, 212, 207, 201,
190, 184, 173, 161, 150, 139, 128, 122, 105, 94, 88, 77, 65, 54, 43,
26, 26, 15, 0, 0, 0, 0, 0, 0, 0, 0, 3, 9, 9, 3,
3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 3, 15, 26, 43, 60, 71, 82, 99, 116, 128, 139,
150, 161, 178, 190, 201, 212, 218, 229, 246, 252, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 252, 246, 240, 235, 224, 218, 212, 195, 173, 139, 122, 99, 77, 71,
65, 65, 71, 82, 94, 105, 116, 128, 139, 150, 161, 173, 184, 190, 195,
195, 201, 195, 201, 195, 195, 190, 178, 173, 167, 161, 150, 139, 128, 128,
116, 105, 99, 82, 71, 60, 48, 37, 26, 20, 9, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 31, 43,
60, 71, 94, 99, 116, 128, 139, 156, 173, 184, 195, 207, 224, 235, 246,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 252,
252, 240, 224, 207, 173, 144, 128, 105, 88, 82, 88, 82, 94, 111, 122,
128, 144, 156, 173, 178, 190, 207, 207, 212, 218, 218, 224, 224, 212, 207,
201, 190, 184, 178, 167, 156, 150, 139, 128, 128, 111, 99, 88, 77, 71,
54, 43, 37, 26, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
3, 9, 9, 15, 9, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 15, 26, 43, 60, 71, 88, 99, 116, 128,
139, 156, 167, 178, 190, 207, 218, 229, 240, 252, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 252, 246, 240, 229, 224, 218, 212, 207, 195,
190, 184, 178, 173, 167, 156, 150, 144, 139, 133, 128, 128, 128, 122, 116,
111, 105, 99, 94, 88, 82, 77, 77, 77, 71, 65, 65, 60, 60, 54,
48, 43, 43, 37, 37, 43, 37, 31, 37, 31, 26, 31, 26, 31, 26,
26, 26, 26, 26, 31, 31, 31, 26, 31, 31, 37, 37, 31, 37, 37,
31, 37, 43, 37, 43, 43, 43, 48, 43, 48, 54, 54, 60, 54, 60,
60, 65, 71, 65, 71, 71, 77, 77, 82, 77, 82, 82, 88, 88, 94,
99, 105, 99, 105, 105, 105, 111, 111, 116, 116, 116, 122, 122, 116, 122,
128, 128, 128, 133, 133, 128, 133, 133, 139, 133, 139, 144, 144, 139, 144,
150, 150, 150, 156, 150, 156, 156, 156, 156, 161, 156, 161, 167, 167, 167,
161, 167, 173, 173, 167, 173, 167, 173, 167, 173, 167, 173, 173, 173, 173,
178, 173, 178, 173, 173, 178, 173, 173, 173, 167, 173, 173, 167, 173, 173,
173, 167, 173, 173, 173, 167, 167, 161, 167, 161, 167, 161, 167, 161, 167,
161, 167, 161, 156, 161, 156, 156, 156, 150, 150, 156, 150, 156, 150, 144,
144, 150, 144, 144, 144, 139, 144, 150, 150, 144, 144, 144, 139, 144, 139,
133, 139, 144, 139, 133, 139, 139, 139, 133, 128, 128, 133, 128, 133, 128,
133, 128, 128, 128, 128, 128, 128, 128, 128, 128, 122, 116, 116, 122, 116,
111, 111, 116, 111, 116, 111, 111, 116, 111, 111, 116, 111, 116, 111, 111,
116, 111, 105, 111, 116, 111, 111, 116, 111, 116, 111, 111, 116, 111, 116,
111, 105, 116};
