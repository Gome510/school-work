function draw(){
    const vw = Math.max(document.documentElement.clientWidth || 0, window.innerWidth || 0)
    const vh = Math.max(document.documentElement.clientHeight || 0, window.innerHeight || 0)
    const centerY = Math.floor((15/21)*vh)
    const centerX = Math.floor((24/34)*vw)
    
    let canvas = document.getElementById("mondrian")
    let context = canvas.getContext('2d')

    
    context.fillStyle = 'rgb(255, 255, 0)'
    context.fillRect(0, 0, 1, 1)


    
}