Tegu on temporary branchiga ehk mõeldud vaid mängu loogika testimiseks. Error-handling suht puudub, aga kui teha lubatud käike, siis mäng töötab ilusti

Aine LTAT.03.025 Henry ja Raido projekt

## Projekt

2 mängija mäng nagu trips-traps-trull

### Reeglid
- 4x4 mängulaud (kokku 16 ruutu)
- kummalgi mängijal on 8 ruudukujulist nuppu
- iga nupu mõlemal poolel on mängija sümbol
- iga nupu üks külg on sinist värvi ja teine külg oranži värvi
- mängijad käivad kordamööda
- käik
    - mängija keerab võimalusel ühe vastase nupu üle serva kõrvalruudule (keerata saab vaid tühjale ruudule, keeramise järel on nupp teistpidi ehk värv vahetub, aga nupu omanik jääb samaks)
    - mängija käib ühe oma nupu tühjale ruudule, enda valitud värv üleval pool
- võitmine
    - võidab see, kes saab esimesena kolm enda samavärvi nuppu järjest horisontaalselt, vertikaalselt või diagonaalselt
    - kui teine mängija saab enda käigu alguses nupu keeramisega kolmese jada ära kõhkuda, pole mäng läbi
    - kui vastane peab oma käigu alguses keerama mängija nupu nii, et mängija sai kolm järjest, on mängija võitnud


### Ehitamine
- `mkdir build`
- `cd build`
- `cmake ..`
- `make`
- `./main`

### dev keskkond

- peale cmake jooksutamist tekkis build kausta compile_commands.json, mida editorid oskavad kasutada, et language server toimiks ilusti.
- peaks toimima: `ln -s build/compile_commands.json compile_commands.json`.
