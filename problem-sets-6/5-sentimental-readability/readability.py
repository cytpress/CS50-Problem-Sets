import cs50

text = cs50.get_string("Text: ")


def main():
    l = count_letters(text)
    w = count_words(text)
    s = count_sentences(text)
    index = calculate_index(l, w, s)
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_letters(text):
    l_count = 0
    for i in range(len(text)):
        if text[i].isalpha():
            l_count += 1
    return l_count


def count_words(text):
    w_count = 0
    for i in range(len(text)):
        if text[i] == " ":
            w_count += 1
    return w_count + 1


def count_sentences(text):
    s_count = 0
    for i in range(len(text)):
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            s_count += 1
    return s_count


def calculate_index(l, w, s):
    index_l = l / w * 100
    index_s = s / w * 100
    index = 0.0588 * index_l - 0.296 * index_s - 15.8
    return round(index)


main()
