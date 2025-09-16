#include <raylib.h>

Color background = CLITERAL(Color) { 0x16, 0x16, 0x16, 0xFF};
static int WIDTH = 1200;
static int HEIGHT = 720;
int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(WIDTH, HEIGHT, "Hheaven");
    InitAudioDevice();

    SetTargetFPS(60);
    
    Wave sample;
    static int rect_w = 100;
    static int rect_y = 100;
    float *samples;
    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(background);
        if (IsFileDropped()) {
            FilePathList path = LoadDroppedFiles();
            sample = LoadWave(path.paths[0]);
            samples = LoadWaveSamples(sample);

            int sampleCount = sample.frameCount;
            int sampleD = sampleCount/rect_w;
            for (int i = 0; i < rect_w; ++i) {
                int index1 = (i * sampleD);
                int index2 = (i + 1) * sampleD;
                float sampleValue1 = 0.0f;
                float sampleValue2 = 0.0f;
                if (sample.channels == 1) {
                    sampleValue1 = samples[index1];
                    sampleValue2 = samples[index2];
                } else if (sample.channels == 2){
                    sampleValue1 = (samples[index1 * 2] + samples[index1 * 2 + 1]) / 0.5f;
                    sampleValue2 = (samples[index2 * 2] + samples[index2 * 2 + 1]) / 0.5f;
                }
                int y1 =  (int) (sampleValue1 * (rect_y/2)) + (rect_y/2);
                int y2 =  (int) (sampleValue2 * (rect_y/2)) + (rect_y/2);

                DrawLine(i, y1, (i + 1), y2, WHITE);
            }

        }
        EndDrawing();
    }
    UnloadWave(sample);
    UnloadWaveSamples(samples);
    CloseAudioDevice();
    CloseWindow();
}
