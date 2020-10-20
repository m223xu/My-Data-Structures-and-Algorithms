def kmp(text, pattern):
    failure = get_failure_array(pattern)
    n = len(text)
    m = len(pattern)
    i, j = 0, 0
    while i < n:
        if text[i] == pattern[j]:
            if j == m - 1:
                return i - j ## first character of the occurrence
            else:
                i += 1
                j += 1
        else:
            if j > 0:
                j = failure[j-1]
            else:
                i += 1
    return -1 ## no match



def get_failure_array(pattern):
    failure = [0]
    i = 1
    j = 0
    while i < len(pattern):
        if pattern[i] == pattern[j]:
            i += 1
            j += 1
            failure.append(j)
        elif j == 0:
            i += 1
            failure.append(j)
        else:
            j = failure[j-1]
    return failure



if __name__ == "__main__":
    pattern = "bababx"
    text = "baxbbabbabababxbaxbb"
    print(kmp(text, pattern))
    pattern = "abacabaca"
    print(get_failure_array(pattern))
    text = "abacabacdabacababacabaca"
    print(kmp(text,pattern))
