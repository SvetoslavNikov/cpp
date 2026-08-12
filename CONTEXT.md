
### Fundamentals — classes & methods

1. Обекти и класове. Дефиниция на клас. Общи понятия и концепции.
2. Методи и параметри. Даннови членове и пропъртита. *(In C++: data members; “properties” ≈ getters/setters.)*
3. Модификатори на достъп в клас. (`public` / `protected` / `private`)
4. Accessor-методи. Mutator-методи.
5. Методи на клас. Видове и модификатори. Припокриване. *(overload; distinguish from override.)*

### Design practices & case-style projects

6. Програмни практики: цифров часовник — диаграми на класове/обекти; проект и програмни елементи.
7. Групиране на обекти. Колекции и итератори. Проект *notebook* — обектна структура, колекции. *(C++: containers, iterators.)*
8. Проектиране на класова йерархия в обектно-структурирана програма.
9. Оценка на качеството на кода. Свързаност и структурираност (coupling / cohesion).
10. Качество на код: дублиращи се фрагменти. Целево-ориентиран проект.
11. Проектиране на обектно-структуриран код.

### C++ object model — lifetime, links, inheritance

12. Класове и обекти: декларация vs дефиниция. Създаване и унищожаване. Структура и обект. (`struct` / `class`)
13. Конструктори и деструктори. Видове конструктори. Методи на клас. *(Ignore “virtual constructors” as a real C++ feature — explain default/copy/move/parameterized; static members/methods.)*
14. Дефиниране на връзки. Взаимодействия на обекти по вертикала и хоризонтала. *(inheritance vs association/composition/aggregation)*
15. Подтипове, подкласове и присвоявания. Предаване на параметри.
16. Наследяване. Полиморфизъм. Достъп до методи и данни на различни нива.
17. Виртуализация и реализация на полиморфизма. Абстрактни класове/методи. Виртуални функции; викане на базови виртуални функции.
18. Вграждане на обекти (composition). Copy-конструктори. Присвоявания и обекти.
19. Референтни параметри (`const` / non-`const`). Работа с референции. Връщане на референции.
20. Конструиране / деструкция на вградени обекти (member subobjects).
21. Заделяне от динамичната памет. Проблеми от взаимодействия между обекти. (`new`/`delete`, ownership)
22. Приятелски класове и функции. Статични членове на клас.
23. Припокриване на оператори — същност, ограничения; аритметични операции.
24. Преобразувания и conversion operators / converting constructors.

### Case: payments system (OOP, not .NET)

25. CASE: обектно-структурирана система за плащане — UML, достъп, методи, права; runtime полиморфизъм и type conversions.
26. Разширяване с интерфейси — полиморфна употреба, наследяване на интерфейс. *(C++: pure abstract classes / concepts as comparison if needed.)*

### Object design principles

31. SOLID; open/closed; single responsibility (регламентирана отговорност).
32. Chain of responsibility.
33. Double dispatch (runtime).
34. Liskov substitution principle. *(Skip .NET contracts part.)*

### Generics / templates & lambdas (C++)

35. Генерични (пораждащи) типове — синтаксис; разлика шаблони (C++) vs generics (.NET processing out of scope).
36. Генерични типове и наследяване; constraints / ограничители. *(C++ templates: specialization, SFINAE/concepts at exam level as needed.)*
37. Lambda-изрази. Функции-обекти и указатели към функции. Предимства.
38. Синтактични елементи на lambda (focus **C++**).
39. Lambda в асинхронни изчисления; определяне на типа на lambda. *(Keep light, C++-oriented.)*

### Parallelism (C++ standard library)

40. Стандартизирани средства в C++ за паралелизация: async tasks, threads, thread-owned resources. Примери.
41. Синхронизация. Атомарни типове. Пример.
42. Mutual exclusion и примитиви. Примери. (`mutex`, locks)
43. Condition variables. Пример.

### Memory, process layout, vulnerabilities (systems view)

48. Обекти в паметта — разполагане; типични програмни грешки.
49. Управление на памет в конзолен режим и Linux: служебни структури; освобождаване (напр. unlink-style ideas where relevant).
50. Buffer overflow — отвътре; code injection. Пример.
51. Атака тип *frontlink*. Пример.
52. Double-free vulnerabilities. Пример.
53. Динамично управление на памет в Windows.
54. Служебни структури в dynamic memory management (Windows).
55. Buffer overflow в Windows и атаки; code injection / control hijack. Пример.

## Skipped (do not study for this track unless asked)

| # | Reason |
|---|--------|
| 27 | .NET interfaces |
| 28 | `*` software contracts |
| 29 | `*` + .NET invariants |
| 30 | `*` contracts & inheritance |
| 44 | `*` + .NET/server async |
| 45 | .NET async primitives |
| 46 | `async`/`await` (.NET/C#) |
| 47 | async context switching (.NET-style) |
| Parts of 34–36, 38 | drop pure .NET/C# details |

## Suggested study progress (optional)

- [ ] Themes 1–5 (class basics)
- [ ] Themes 12–24 (C++ object model)
- [ ] Themes 8–11, 31–34 (design)
- [ ] Themes 6–7, 25–26 (case / collections)
- [ ] Themes 35–43 (templates, lambdas, concurrency)
- [ ] Themes 48–55 (memory & vulnerabilities)
- [ ] Practice CLI exercises under exam-like time limits

---

*When starting a new chat: attach or `@` this file (and optionally `c++conspect.md`). Ask for a specific theme number, a theory draft, or a CLI practice task.*
