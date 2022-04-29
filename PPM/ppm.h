//
// Created by Victor on 25/04/2022.
//

#ifndef PPM_PPM_H
#define PPM_PPM_H

void check_context(int ch, int maxContext, int *currentContext, int *ccSize);
int escape_count(struct freqs *freq, const int *currentContext, int ccSize, int maxContext, int maxDepth);
void start_model(struct freqs *freq, struct cum_freqs *cum_freq);
void create_table(struct freqs freq[], struct cum_freqs cum_freq[]);
void update_model(struct freqs *freq, struct cum_freqs *cum_freq, const int *context, int cSize);
struct cum_freqs *gotoTable(int escapeCount, struct cum_freqs *cum_freq, struct cum_freqs *cum_freq_1, const int *context, int maxContext, int maxDepth);

#endif //PPM_PPM_H
