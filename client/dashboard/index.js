console.log('Javascript file works');
document.querySelector('#getData').addEventListener('click', () => {
    console.log('click')
    // fetch("http://127.0.0.1:2022/getData")
    //     .then(x => x.json())
    //     .then(y => console.log(y));
    fetch("http://localhost:2022/getData")
        .then(x => x.json())
        .then(y => console.log(y));
})