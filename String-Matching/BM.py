def bm(text, pattern):
    last_occurrence = get_last_occurrence(pattern)
    n = len(text)
    m = len(pattern)
    i, j = m - 1, m - 1
    while i < n and j >= 0:
        if text[i] == pattern[j]:
            i -= 1
            j -= 1
        else:
            i += (m - 1 - min(last_occurrence[ord(text[i])], j - 1))
            j = m - 1
    if j == -1:
        return i + 1
    else:
        return -1


## Bad character heuristic
def get_last_occurrence(pattern):
    last_occurrence = [-1 for i in range(256)]
    for i in range(len(pattern)):
        last_occurrence[ord(pattern[i])] = i
    return last_occurrence



if __name__ == "__main__":
    text = "abacabacdabacababacabaca"
    pattern = "abacabaca"
    print(bm(text,pattern))