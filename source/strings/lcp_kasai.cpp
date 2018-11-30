for (int i = 0; i < n; i++) {
    cin >> suf[i];
    suf[i]--;
    fus[suf[i]] = i;
}
int k = 0;
for (int i = 0; i < n; i++) {
    if (k > 0) k--;
    if (fus[i] == n - 1)
        k = 0;
    else {
        while (max(i, suf[fus[i] + 1]) + k < n && s[i + k] == s[suf[fus[i] + 1] + k])
            k++;
    }
    lcp[fus[i]] = k;
}
