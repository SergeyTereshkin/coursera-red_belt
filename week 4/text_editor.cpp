#include <string>
#include "test_runner.h"
#include "profile.h"
#include <profile.h>
#include <list>
using namespace std;

class Editor {
public:
    // Р РµР°Р»РёР·СѓР№С‚Рµ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ Рё РѕР±СЉСЏРІР»РµРЅРЅС‹Рµ РјРµС‚РѕРґС‹
    Editor() {
        text = {'|'};
        cursor_position = begin(text);
    }
    void Left() {
        if (cursor_position != begin(text)) {
            swap(*prev(cursor_position), *cursor_position);
            cursor_position = prev(cursor_position);
        }
    }
    void Right() {
        if (cursor_position != prev(end(text))) {
            swap(*cursor_position, *next(cursor_position));
            cursor_position = next(cursor_position);
        }
    }
    void Insert(char token) {
        text.insert(cursor_position, token);
    }
    void Cut(size_t tokens = 1) {
        buffer.clear();
        auto it = next(cursor_position);
        while (it != next(cursor_position, tokens + 1) and it != end(text)) {
            buffer.push_back(*it);
            it++;
        }
        text.erase(next(cursor_position), it);
    }
    void Copy(size_t tokens = 1) {
        buffer.clear();
        for (auto it = next(cursor_position); it != next(cursor_position, tokens + 1); it++) {
            buffer.push_back(*it);
        }
    }
    void Paste() {
        for (const auto& b : buffer) {
            Insert(b);
        }
    }
    string GetText() const {
        string text_string;
        for (const auto& s : text) {
            if (s != '|')
            text_string.push_back(s);
        }
        return text_string;
    }

private:
    list<char> text;
    list<char> buffer;
    list<char>::iterator cursor_position;
};

void TypeText(Editor& editor, const string& text) {
    for(char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
            Editor editor;

            const size_t text_len = 12;
            const size_t first_part_len = 7;
            TypeText(editor, "hello, world");
            //cout << editor.GetText() << endl; // hello, world|
            for (size_t i = 0; i < text_len; ++i) {
                editor.Left();
            }
            //cout << editor.GetText() << endl; // |hello, world
            editor.Cut(first_part_len);
            //cout << editor.GetText() << endl; // |world
            for (size_t i = 0; i < text_len - first_part_len; ++i) {
                editor.Right();
            }
            //cout << editor.GetText() << endl; // world|
            TypeText(editor, ", ");
            //cout << editor.GetText() << endl; // world, |
            editor.Paste();
            //cout << editor.GetText() << endl; // world, hello, |`
            editor.Left();
            editor.Left();
            //cout << editor.GetText() << endl; // world, hello|,
            editor.Cut(3);
            //cout << editor.GetText() << endl; // world, hello|

            ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for(char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}
