#include "kws_guess.h"
#include "kws_vfs.h"
#include "fe.h"
#include "kann.h"
#include <assert.h>
#include "stdio.h"

static const char LOG_TAG[] = "[kws_guess]";

static kann_t *g_ann;

void kws_guess_init(const char* name)
{
    assert(sizeof(float) == 4);
    kws_fs_create(name);
    g_ann = kann_load(name);
    assert(g_ann);
    assert(kann_dim_in(g_ann) == 13*49);
}

static float* kws_fe_one_sec_16b_16k_mono(int16_t samples[16000])
{
    int n_frames, n_items_in_frame;
    csf_float *feat;

    n_frames = n_items_in_frame = 0;
    feat = fe_mfcc_16k_16b_mono(samples, 16000, &n_frames, &n_items_in_frame);
    assert(n_frames == 49);
    assert(n_items_in_frame == 13);
    assert(n_items_in_frame > 0);
    assert(feat);

    // for(int i = 0, idx = 0; i < n_frames; i++)
    // {
    //     for(int k = 0; k < n_items_in_frame; k++, idx++)
    //     {
    //         if(k)
    //         {
    //             printf(" ");
    //         }
    //         printf("%.3f", feat[idx]);
    //     }
    //     printf("\n");
    // }

    return feat;
}

static const float* kws_guess_fe(float* feat)
{
    const float* out = kann_apply1(g_ann, feat);
    assert(out);

    // for (int i = 0; i < kann_dim_out(g_ann); i++)
    // {
    //     if (i)
    //     {
    //         putchar(' ');
    //     }
    //     printf("%f", out[i]);
    // }
    // putchar('\n');

    return out;
}

const float* kws_guess_one_sec_16b_16k_mono(int16_t* samples)
{
    float* feat = kws_fe_one_sec_16b_16k_mono(samples);
    const float* out = kws_guess_fe(feat);
    free(feat);

    return out;
}

int kws_guess_dim_out()
{
    return kann_dim_out(g_ann);
}