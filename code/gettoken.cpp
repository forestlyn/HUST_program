#include "gettoken.h"
char token_text[50]; //存放单词自身值
char string_num[50]; //存放数字的字符串
int lines = 1;
int isRight(char *p)
{
  int i, j, flag;
  for (i = 0; i < KEYTYPE_LEN; i++)
  {
    int l = strlen(KeyType[i]);
    for (j = 0; j < l; j++)
    {
      if (p[j] == KeyType[i][j] || p[j] == KeyType[i][j] + 'a' - 'A')
      {
        if (p[j] == 'l' || p[j] == 'L')
          flag = 1;
        continue;
      }
    }
    if (p[j] == '\0')
      return 1 + flag;
  }
  return 0;
}
int isXnum(char c)
{
  return (('a' <= c && c <= 'f') || ('A' <= c && c <= 'F') || isNum(c));
}
int isNum(char c)
{
  return ('0' <= c && c <= '9');
}
int isLetter(char c)
{
  return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}
int addWord(char c, char *word)
{
  int i = 0;
  while (word[i] != '\0' && i <= 19)
    i++;
  if (i >= 19)
    return -1;
  word[i] = c;
  return 1;
}
int getToken(FILE *fp)
{
  char c;
  memset(token_text, 0, sizeof(token_text));
  c = getc(fp);
  //跳过空格转行
  while (c == ' ' || c == '\n')
  {
    if (c == '\n')
      lines++;
    c = getc(fp);
  }

  //关键字和IDENT
  if (isLetter(c) || c == '_')
  {
    int i;
    addWord(c, token_text);
    c = getc(fp);
    while (isLetter(c) || isNum(c) || c == '_')
    {
      addWord(c, token_text);
      c = getc(fp);
    }
    ungetc(c, fp);
    for (i = 0; i <= KEYWORD_LEN; i++)
    {
      if (!strcmp(KeyWords[i], token_text))
      {
        return IF + i;
      }
    }
    if (!strcmp("unsigned", token_text))
      return UNSIGNED;
    if (!strcmp("int", token_text))
      return INT;
    if (!strcmp("char", token_text))
      return CHAR;
    if (!strcmp("float", token_text))
      return FLOAT;
    if (!strcmp("long", token_text))
      return LONG;
    if (!strcmp("short", token_text))
      return SHORT;
    if (!strcmp("double", token_text))
      return DOUBLE;
    c = getc(fp);
    if (c == '[')
    {
      addWord(c, token_text);
      c = getc(fp);
      while (isNum(c))
      {
        addWord(c, token_text);
        addWord(c, string_num);
        c = getc(fp);
      }
      if (c != ']')
        return ERROR_TOKEN;
      else
      {
        addWord(c, token_text);
        return ARRAY;
      }
    }
    else
    {
      ungetc(c, fp);
      return IDENT;
    }
  }

  //判断数
  if (isNum(c))
  {
    if (c == '0')
    {
      addWord(c, token_text);
      c = getc(fp);
      if (c == 'x' || c == 'X')
      {
        addWord(c, token_text);
        c = getc(fp);
        if (isXnum(c))
        {
          addWord(c, token_text);
          c = getc(fp);
          while (isXnum(c))
          {
            addWord(c, token_text);
            c = getc(fp);
          }
          if (c == ' ' || c == ';' || c == ',')
          {
            ungetc(c, fp);
            return INT_CONST;
          }
          return ERROR_TOKEN;
        }
        else
        {
          return ERROR_TOKEN;
        }
      }
      else if ('0' <= c && c <= '7')
      {
        addWord(c, token_text);
        c = getc(fp);
        while ('0' <= c && c <= '7')
        {
          addWord(c, token_text);
          c = getc(fp);
        }
        if (c == ' ' || c == ';' || c == ',')
        {
          ungetc(c, fp);
          return INT_CONST;
        }
        return ERROR_TOKEN;
      }
      if (c == ' ' || c == ';' || c == ',')
      {
        ungetc(c, fp);
        return INT_CONST;
      }
      return ERROR_TOKEN;
    }
    while (isNum(c))
    {
      addWord(c, token_text);
      c = getc(fp);
    }
    if (c != '.' && c != 'u' && c != 'U' && c != 'l' && c != 'L')
    {
      if (c != ' ' && c != ';' && c != ')' && c != '+' && c != '-' && c != '*' && c != '/')
        return ERROR_TOKEN;
      ungetc(c, fp);
      return INT_CONST;
    }
    else if (c == '.')
    {
      c = getc(fp);
      if (!isNum(c))
        return ERROR_TOKEN;
      else
      {
        addWord('.', token_text);
        addWord(c, token_text);
        c = getc(fp);
        while (isNum(c))
        {
          addWord(c, token_text);
          c = getc(fp);
        }
        if (c == 'F' || c == 'f')
        {
          addWord(c, token_text);
          return FLOAT_CONST;
        }
        ungetc(c, fp);
        return FLOAT_CONST;
      }
    }
    else if (c == 'u' || c == 'U' || c == 'L' || c == 'l')
    {
      char p[20];
      addWord(c, p);
      addWord(c, token_text);
      c = getc(fp);
      while (c == 'u' || c == 'U' || c == 'L' || c == 'l')
      {
        addWord(c, token_text);
        addWord(c, p);
        c = getc(fp);
      }
      ungetc(c, fp);
      if (isRight(p) == 1)
        return INT_CONST;
      else if (isRight(p) == 2)
        return LONG_CONST;
      else
        return ERROR_TOKEN;
    }
    else
      return ERROR_TOKEN;
  }

  switch (c)
  {
  //float
  case '.':
    c = getc(fp);
    while (isNum(c))
    {
      addWord(c, token_text);
      c = getc(fp);
    }
    if (c == 'f' || c == 'F')
    {
      return FLOAT_CONST;
    }
    else
    {
      ungetc(c, fp);
      return FLOAT_CONST;
    }
    break;

  //char
  case '\'':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '\'')
      return ERROR_TOKEN;
    if (c != '\\')
    {
      addWord(c, token_text);
      c = getc(fp);
      if (c != '\'')
      {
        return ERROR_TOKEN;
      }
      else
      {
        addWord(c, token_text);
        return CHAR_CONST;
      }
    }
    else
    {
      addWord(c, token_text);
      c = getc(fp);
      if (c == 'n' || c == '\\' || c == '\'' || c == '"' || c == '?' || c == 'a' ||
          c == 'b' || c == 'f' || c == 'r' || c == 't' || c == 'v')
      {
        addWord(c, token_text);
        c = getc(fp);
        if (c == '\'')
        {
          addWord(c, token_text);
          return CHAR_CONST;
        }
        else
        {
          return ERROR_TOKEN;
        }
      }
      if (c == 'x')
      {
        addWord(c, token_text);
        c = getc(fp);
        int flag = 0;
        while (isXnum(c))
        {
          addWord(c, token_text);
          flag++;
          c = getc(fp);
        }
        if (!flag || flag > 2 || c != '\'')
          return ERROR_TOKEN;
        addWord(c, token_text);
        return CHAR_CONST;
      }
      if ('0' <= c && c <= '7')
      {
        addWord(c, token_text);
        c = getc(fp);
        int flag = 1;
        while ('0' <= c && c <= '7')
        {
          addWord(c, token_text);
          flag++;
          c = getc(fp);
        }
        if (flag > 3 || c != '\'')
          return ERROR_TOKEN;
        addWord(c, token_text);
        return CHAR_CONST;
      }
    }
    break;

  //string
  case '"':
    do
    {
      if (c != '\\')
      {
        addWord(c, token_text);
      }
      else
      {
        c = getc(fp);
        addWord(c, token_text);
      }
      c = getc(fp);
    } while (c != '\n' && c != '"');
    if (c != '"')
      return ERROR_TOKEN;
    else
    {
      addWord(c, token_text);
      return STRING_CONST;
    }
    break;

    //除法，注释
  case '/':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '/')
    {
      do
      {
        addWord(c, token_text);
        c = getc(fp);
      } while (c != '\n');
      ungetc(c, fp);
      return ANNO;
    }
    else if (c == '*')
    {
      while (1)
      {
        addWord(c, token_text);
        c = getc(fp);
        if (c == '*')
        {
          addWord(c, token_text);
          c = getc(fp);
          if (c == '/')
          {
            addWord(c, token_text);
            return ANNO;
          }
        }
      }
    }
    else
    {
      ungetc(c, fp);
      return DIVIDE;
    }
    break;

  case '#':
    addWord(c, token_text);
    c = getc(fp);
    if (isLetter(c))
    {
      do
      {
        addWord(c, token_text);
        c = getc(fp);
      } while (isLetter(c));
      if (!strcmp(token_text, "#include"))
      {
        while (c != '\n')
        {
          addWord(c, token_text);
          c = getc(fp);
        }
        ungetc(c, fp);
        return INCLUDE;
      }
      else if (!strcmp(token_text, "#define"))
      {
        while (c != '\n')
        {
          addWord(c, token_text);
          c = getc(fp);
        }
        ungetc(c, fp);
        return MACRO;
      }
      else
        return ERROR_TOKEN;
    }
    else
      return ERROR_TOKEN;
    break;

  case '{':
    addWord(c, token_text);
    return LB;

  case '}':
    addWord(c, token_text);
    return RB;

  case '[':
    addWord(c, token_text);
    return LM;

  case ']':
    addWord(c, token_text);
    return RM;

  case '(':
    addWord(c, token_text);
    return LP;

  case ')':
    addWord(c, token_text);
    return RP;

  case ',':
    addWord(c, token_text);
    return COMMA;

  case ';':
    addWord(c, token_text);
    return SEMI;

  case '*':
    addWord(c, token_text);
    return TIMES;

  case '=':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '=')
    {
      addWord(c, token_text);
      return EQ;
    }
    else
    {
      ungetc(c, fp);
      return ASSIGN;
    }

  case '!':
    c = getc(fp);
    if (c == '=')
    {
      addWord('!', token_text);
      addWord(c, token_text);
      return NEQ;
    }
    else
    {
      return ERROR_TOKEN;
    }

  case '+':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '+')
    {
      addWord(c, token_text);
      return PLUSPLUS;
    }
    else
    {
      ungetc(c, fp);
      return PLUS;
    }

  case '-':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '-')
    {
      addWord(c, token_text);
      return MINUSMINUS;
    }
    else
    {
      ungetc(c, fp);
      return MINUS;
    }

  case '%':
    addWord(c, token_text);
    return MOD;

  case '>':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '=')
    {
      addWord(c, token_text);
      return MOREEQUAL;
    }
    else
    {
      ungetc(c, fp);
      return MORE;
    }

  case '<':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '=')
    {
      addWord(c, token_text);
      return LESSEQUAL;
    }
    else
    {
      ungetc(c, fp);
      return LESS;
    }
  case '&':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '&')
    {
      addWord(c, token_text);
      return ANDAND;
    }
    else
    {
      ungetc(c, fp);
      return ERROR_TOKEN;
    }
  case '|':
    addWord(c, token_text);
    c = getc(fp);
    if (c == '|')
    {
      addWord(c, token_text);
      return OROR;
    }
    else
    {
      ungetc(c, fp);
      return ERROR_TOKEN;
    }

  case EOF:
    return -1;

  default:
    break;
  }
}
