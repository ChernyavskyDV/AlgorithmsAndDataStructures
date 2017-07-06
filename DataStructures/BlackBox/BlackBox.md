<h1>Черный ящик
<h4>Имя входного файла: input.txt
<h4>Имя выходного файла: output.txt
<h6>Чёрный ящик организован наподобие примитивной базы данных. Он может хранить набор целых чисел и имеет выделенную переменную i. В начальный момент времени чёрный ящик пуст, а значение переменной i равно нулю. Чёрный ящик обрабатывает последовательность поступающих команд (запросов). Существуют два вида запросов:
<h6>Add(x) — положить в чёрный ящик элемент x;
Get — увеличить значение переменной i на 1 и выдать копию i-го по величине элемента чёрного ящика (напомним, что i-м по величине элементом называется число, стоящее на i-м месте в отсортированной по неубыванию последовательности элементов чёрного ящика).
Необходимо разработать эффективный алгоритм, обрабатывающий заданную последовательность поступающих команд (запросов) за время O(M log M), где M — количество запросов Add.
<h3>Входные данные
<h6>В первой строке задано число M (1 ≤ M ≤ 910 000) — количество запросов Add и число N — количество запросов Get.
Во второй строке — последовательность включаемых в чёрный ящик элементов A1, A2, …, AM — целые числа, не превосходящие по абсолютной величине 2 000 000 000.
В третьей строке — последовательность u1, u2, …, uN, задающая количество содержащихся в чёрном ящике элементов в момент выполнения первой, второй, …, N-й команды Get.
Числа в строках разделены одним или несколькими пробелами.
<h6>Схема работы чёрного ящика предполагает, что последовательность натуральных чисел u1, u2, …, uN упорядочена по неубыванию, N ≤ M и для всех p (1 ≤ p ≤ N) выполняется соотношение p ≤ up ≤ M. Последнее следует из того, что для p-го элемента последовательности u мы выполняем запрос Get, выдающий p-е по величине число из набора A1, A2, …, Aup.
<h3>Выходные данные
<h6>В выходной файл выводится полученная последовательность ответов чёрного ящика для заданной последовательности запросов (т. е. результаты работы команды Get). Числа выводятся в одну строку через пробел. После последнего числа не должно быть пробела.
<h3>Пример
<h4>input.txt
<h6>6 4
<h6>3 1 -4 2 8 -1000
<h6>1 2 6 6
<h4>output.txt
<h6>3 3 1 2