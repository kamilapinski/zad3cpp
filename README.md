<div class="no-overflow"><h1>Turniej rycerski</h1>

<h2>Wstęp</h2>

<p>Rozwiązując to zadanie, studenci powinni poznać:</p>

<ul>
<li>rodzaje i dostępność konstruktorów,</li>
<li>tworzenie operatorów jako metod klasowych i funkcji globalnych,</li>
<li>operatory porównujące,</li>
<li>jawne i niejawne konwersje typów,</li>
<li>listy inicjujące,</li>
<li>użycie słów kluczowych <code>const</code>, <code>constexpr</code>, <code>consteval</code> i <code>constinit</code>,</li>
<li>użycie słowa kluczowego <code>inline</code>.</li>
</ul>

<h2>Polecenie</h2>

<p>Zadanie polega na zaimplementowaniu modułu <code>knights</code> pozwalającego na
rozegranie turnieju rycerskiego o puchar króla lub rękę królewny, odciśniętą
rzecz jasna w kamieniu. W ramach tego modułu powinny być udostępnione
następujące klasy:</p>

<ul>
<li><p><code>Knight</code>     – reprezentująca pojedynczego dzielnego rycerza;</p></li>
<li><p><code>Tournament</code> – reprezentująca turniej rycerski.</p></li>
</ul>

<p>Każdy rycerz klasy <code>Knight</code> powinien posiadać pewną liczbę sztuk złota
na zacny posiłek po trudach walki i zakup pamiątek w wiosce turniejowej.
Co jednak ważniejsze, powinien władać bronią i nosić zbroję, których
wartość bojowa jest określona pewną ich klasą. Im wyższa klasa broni albo
zbroi, tym są one silniejsze. Klasa o zerowej wartości oznacza brak
broni albo zbroi. Złoto oraz klasy broni i zbroi są liczbami
całkowitymi typu <code>size_t</code>.</p>

<p>Klasa <code>Knight</code> powinna udostępniać:</p>

<ul>
<li><p>stałą <code>MAX_GOLD</code> reprezentującą maksymalną liczbę sztuk złota, które może
posiadać rycerz, czyli maksymalną wartość typu <code>size_t</code>.</p></li>
<li><p>tworzenie obiektu (rycerza) z trzema parametrami (liczba sztuk złota,
klasa broni i klasa zbroi). Nie powinno być możliwości tworzenia
obiektu bez podania tych parametrów.</p></li>
<li><p>tworzenie obiektu za pomocą domyślnego kopiowania oraz przenoszenia.</p></li>
<li><p>domyślne operacje przypisania w wersji kopiującej i przenoszącej.</p></li>
<li><p>pozyskanie informacji o złocie trzymanym przez rycerza, o klasie dzierżonej
broni i klasie przywdzianej zbroi.</p></li>
<li><p>dorzucenie rycerzowi do sakwy podanej liczby sztuk złota, ale tylko do
momentu osiągnięcia dopuszczalnego maksimum.</p></li>
<li><p>zmuszenie rycerza do oddania całego złota, zmiany broni na inną o podanej
klasie, oddania całej broni, przebrania się w inną zbroję o podanej klasie
oraz oddania zbroi.</p></li>
<li><p>zabranie drugiemu rycerzowi całego jego złota i tylko lepszych (w sensie
klasy) składników jego wyposażenia. Tę operację powinien realizować
operator <code>+=</code>.</p></li>
<li><p>utworzenie nowego rycerza w wyniku operacji „dodawania” (operator <code>+</code>)
dwóch rycerzy. Nowy rycerz ma mieć tyle złota, ile mają łącznie „dodawani”
rycerze, ale maksymalnie <code>MAX_GOLD</code> sztuk, oraz lepsze składniki ich
wyposażenia.</p></li>
<li><p>porównywanie rycerzy (operatory <code>&lt;=&gt;</code> i <code>==</code>), które odpowiada na pytanie,
kiedy jeden rycerz może pokonać drugiego. Pojedynek (porównanie) wygrywa
przede wszystkim ten wojownik, którego broń jest silniejsza od zbroi
przeciwnika i którego klasa zbroi jest jednocześnie nie mniejsza niż klasa
broni jego przeciwnika. Ponadto, jeśli obaj rycerze mają broń silniejszą
od zbroi przeciwnika, to zwycięża ten z lepszą zbroją albo lepszą
bronią, gdy zbroje są tej samej klasy. W pozostałych przypadkach będzie
remis, co oznacza, że porównywani rycerze są sobie równi.</p></li>
<li><p>wypisywanie na standardowe wyjście informacji o rycerzu w postaci
<code>(liczba sztuk złota, klasa broni, klasa zbroi)</code>.</p></li>
</ul>

<p>Należy zapewnić, żeby obiekt klasy <code>Knight</code> mógł być używany w wyrażeniach
stałych <code>constexpr</code>. Ponadto w wyrażeniach stałych powinny być dostępne
wszystkie metody, które nie zmieniają stanu obiektu tej klasy. Oprócz tego
powinna być dostępna globalna stała <code>TRAINEE_KNIGHT</code> inicjowana tylko podczas
kompilowania, która reprezentuje praktykanta rycerskiego nieposiadającego
żadnego złota oraz mającego broń i zbroję klasy pierwszej.</p>

<p>W drugiej wymaganej w zadaniu klasie <code>Tournament</code> powinna być możliwość:</p>

<ul>
<li><p>przechowywania listy pretendentów do tytułu zwycięzcy oraz listy rycerzy
wyeliminowanych z turnieju. Kolejność w liście turniejowej określa
kolejność, w jakiej rycerze będą stawali do walki. Natomiast rycerze
w liście wyeliminowanych są ułożeni w odwrotnej kolejności odpadania
z turnieju.</p></li>
<li><p>utworzenia obiektu (turnieju) w oparciu o listę rycerzy przekazaną
poprzez parametr. Jeśli podana lista będzie pusta, to jedynym pretendentem
w turnieju powinien być praktykant rycerski. Tworzenie turnieju bez
podania żadnego parametru nie powinno być możliwe.</p></li>
<li><p>utworzenia obiektu za pomocą kopiowania i przenoszenia oraz realizacji
operacji przypisania w wersji kopiującej i przenoszącej.</p></li>
<li><p>dodawania rycerza na koniec listy pretendentów za pomocą operatora <code>+=</code>.</p></li>
<li><p>wycofania z turnieju wszystkich zawodników mających wszystkie parametry,
czyli złoto, klasę broni i klasę zbroi, identyczne jak podany rycerz,
wykorzystując w tym celu operator <code>-=</code>.</p></li>
<li><p>rozegrania turnieju. Wynikiem tej operacji powinien być stały iterator
do kontenera z pretendentami, wskazujący zwycięzcę lub koniec kontenera
(<code>end()</code>) w przypadku braku zwycięzcy turnieju. Zasady turnieju są
następujące:</p>

<ul>
<li>do walki stają zawsze dwaj pierwsi pretendenci, którzy zdejmowani są
z listy turniejowej;</li>
<li>walka polega na porównaniu tych dwóch pretendentów;</li>
<li>zwycięzca przejmuje złoto przegranego i lepsze składniki jego wyposażenia
(broń, zbroję);</li>
<li>wygrany wstawiany jest na koniec listy pretendentów;</li>
<li>przegrany wstawiany jest do listy wyeliminowanych;</li>
<li>w przypadku remisu obaj rycerze zachowują swoje złoto i wyposażenie,
ale trafiają do listy wyeliminowanych;</li>
<li>turniej kończy się, gdy w liście pretendentów pozostanie jeden (zwycięzca)
lub zero (nie ma zwycięzcy) rycerzy;</li>
<li>rycerze trafiający do listy wyeliminowanych wstawiani są na jej początek;</li>
<li>przy remisie kolejność rycerzy wyeliminowanych pozostaje taka sama,
jak była na liście pretendentów.</li>
</ul></li>
<li><p>uzyskania stałego iteratora oznaczającego brak zwycięzcy turnieju.</p></li>
<li><p>uzyskania informacji o rozmiarze turnieju, czyli łącznej liczbie rycerzy
biorących w nim udział (zarówno pretendentów, jak i wyeliminowanych).</p></li>
<li><p>wypisania na standardowym wyjściu aktualnej listy pretendentów oraz
rycerzy wyeliminowanych. Wydruk każdego pretendenta powinien być
poprzedzony prefiksem <code>"+ "</code>, zaś rycerza wyeliminowanego prefiksem <code>"- "</code>
Koniec wydruku należy oznaczać linią zawierającą znak <code>'='</code>.</p></li>
</ul>

<p>Na początku każdego rozegrania turnieju lista wyeliminowanych rycerzy
powinna być czyszczona. To samo czyszczenie ma się odbywać także w przypadku
każdej operacji zmieniającej zawartość listy pretendentów.</p>

<p>Na koniec należy zdefiniować globalną funkcję <code>max_diff_classes</code>, pobierającą
listę rycerzy i dającą w wyniku parę (<code>std::pair</code>) z klasami broni i zbroi,
których różnica jest w tej liście największa. Funkcja ta może
być wykonywana tylko podczas kompilowania.</p>

<h2>Wymagania formalne</h2>

<p>Oczekiwane rozwiązanie powinno korzystać z kontenerów i metod udostępnianych
przez standardową bibliotekę C++.</p>

<p>Należy ukryć przed światem zewnętrznym wszystkie zmienne globalne i funkcje
pomocnicze nienależące do wyspecyfikowanego interfejsu modułu.</p>

<p>Rozwiązanie powinno zawierać plik <code>knights.h</code> oraz opcjonalnie plik
<code>knights.cpp</code>. Pliki te należy umieścić w Moodle. Rozwiązanie będzie kompilowane
na maszynie <em>students</em> poleceniem</p>

<pre><code>g++ -Wall -Wextra -O2 -std=c++20 *.cpp
</code></pre>

<h2>Ocenianie rozwiązania</h2>

<h3>Ocena automatyczna</h3>

<p>Za testy automatyczne zostanie przyznana ocena z przedziału od 0 do 6 punktów.
Za błędną nazwę pliku zostanie odjęty 1 punkt. Za ostrzeżenia wypisywane przez
kompilator zostanie odjęty 1 punkt. Nie ma punktów ułamkowych.</p>

<h3>Ocena jakości kodu</h3>

<p>Ocena jakości kodu jest z przedziału od 0 do 4 punktów. Nie ma punktów
ułamkowych. Odejmujemy punkty za:</p>

<ul>
<li><p>brzydkie formatowanie kodu (niepoprawne wstawianie spacji, wcięć, odstępów,
brak komentarzy, magiczne stałe itd.);</p></li>
<li><p>nieprawidłowe, niedostateczne używanie <code>const</code>, o ile testy tego nie wykryły;</p></li>
<li><p>zły dobór typu lub kontenera, brak nazw typów, niewiele mówiące nazwy typów;</p></li>
<li><p>rozwlekłą lub nieelegancką strukturę programu, rozpatrywanie zbyt wielu
warunków brzegowych, powtarzanie kodu, przechowywanie liczb jako napisów;</p></li>
<li><p>korzystanie z wejścia-wyjścia dostarczanego przez bibliotekę C zamiast ze
strumieni;</p></li>
<li><p>nieuzasadnione przekazywanie funkcjom przez wartość dużych obiektów;</p></li>
<li><p>deklarowanie składowych lub metod jako <code>public</code>, gdy wystarczyłoby <code>private</code>
lub <code>protected</code>, nadużywanie relacji <code>friend</code>;</p></li>
<li><p>niezgodność interfejsu klas z treścią zadania;</p></li>
<li><p>brak użycia operatora <code>&lt;=&gt;</code>, definiowanie zbyt wielu operatorów
lub zbyt wielu wersji operatorów;</p></li>
<li><p>brak użycia listy inicjującej w konstruktorze;</p></li>
<li><p>wprowadzanie sztucznych ograniczeń na rozmiar danych;</p></li>
<li><p>nieusuwanie lub nieefektywne usuwanie niepotrzebnych już danych;</p></li>
<li><p>brak <em>header guard</em>;</p></li>
<li><p>nieukrycie przed światem zewnętrznym wszystkich zmiennych globalnych
i funkcji pomocniczych nienależących do wyspecyfikowanego interfejsu modułu;</p></li>
<li><p>użycie <code>typedef</code> zamiast <code>using</code>;</p></li>
<li><p>inne znalezione i niewymienione w powyższych kryteriach błędy i niezgodności
z treścią zadania lub odpowiedziami udzielonymi na forum, a niewykryte
przez testy automatyczne;</p></li>
<li><p>niezastosowanie się do uwag udzielonych w poprzednich zadaniach.</p></li>
</ul>

<p>Nie wymagamy jeszcze prawidłowego oznaczania metod niezgłaszających wyjątków.</p>

<h2>Przykłady użycia</h2>

<p>Przykłady użycia modułu <code>knights</code> znajdują się w pliku <code>knights_example.cpp</code>.
Przykłady wydruków wypisywanych przez program <code>knights_example</code> znajdują się
w pliku <code>knights_example.out</code>. Przykłady te są integralną częścią specyfikacji
zadania.</p>

<p>Kompilowanie przykładu:</p>

<pre><code>g++ -Wall -Wextra -O2 -std=c++20 knights_example.cpp -o knights_example
</code></pre>

<p>lub</p>

<pre><code>g++ -c -Wall -Wextra -O2 -std=c++20 knights_example.cpp
g++ -c -Wall -Wextra -O2 -std=c++20 knights.cpp
g++ knights_example.o knights.o -o knights_example
</code></pre>
</div>
