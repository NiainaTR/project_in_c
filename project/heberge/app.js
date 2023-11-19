let listItem = [];
let tabIndex = [];
let i = 1;
let nbr = 0;



const div = document.querySelector('.configuration');
const btnAdd = document.getElementById('add');
const createbtn = document.getElementById('createbtn');
const hiddenInputNbr = document.getElementById('hiddenInputNbr');
const hiddenInputTab = document.getElementById('hiddenInputTab');


createbtn.addEventListener('click' , e =>{
    hiddenInputNbr.setAttribute('value' , nbr);
    let str = "";
    for(let i of tabIndex){
      str += i + " ";
    }
    hiddenInputTab.setAttribute('value' , str);    
})


btnAdd.addEventListener('click' , e => {
    
    let id = String(Date.now())

    addNewElementToDom(id);
    
})


function addNewElementToDom(id){
    const element = document.createElement('div');
    
    i++;
    tabIndex.push(i);
    
    nbr++;

    element.setAttribute('i' , i);
    element.setAttribute('item-id' , id);
    

    
    element.classList.add('configuration')

    
    element.innerHTML = `
          <p>Configuration</p>
                <div>
                  <label class="form-label">Directory</label>
                  <input type="text" class="form-control" name="Directory${i}" required>
                </div>
                <div>
                  <label class="form-label">ScriptAlias</label>
                  <input type="text" class="form-control" name="Scriptalias${i}" required>
                </div>
                <div class="config" style="margin-top: 20px;">
                      <div class="mb-3 form-check">
                        <input type="checkbox" class="form-check-input" id="exampleCheck1" name="index${i}">
                        <label class="form-check-label" for="exampleCheck1">Indexes</label>
                      </div>
                    <div class="mb-3 form-check">
                        <input type="checkbox" class="form-check-input" id="exampleCheck1" name="follow${i}">
                        <label class="form-check-label" for="exampleCheck1">FollowSymLinks</label>
                    </div>
                    <div class="mb-3 form-check">
                      <input type="checkbox" class="form-check-input" id="exampleCheck1" name="exec${i}">
                      <label class="form-check-label" for="exampleCheck1">ExecCgi</label>
                    </div>
                    <label class="form-check-label" for="exampleCheck1">AddHandler</label>
                    <select class="form-select" aria-label="Default select example" name="add${i}">
                      <option value="cgi${i}">.cgi</option>
                      <option value="pl${i}">.pl</option>
                      <option value="py${i}">.py</option>                    
                    </select>
                    <label class="form-check-label" for="exampleCheck1">AllowOverride</label>
                    <select class="form-select" aria-label="Default select example" name="allow${i}">
                      <option value="all${i}">All</option>
                      <option value="none${i}">None</option>
                    </select>
                  </div>  
    `
    const hr = document.createElement('hr');
    
    const btnDel = document.createElement('button');
    
    btnDel.setAttribute('item-id' , id);
    btnDel.setAttribute('i' , i);
    

    btnDel.classList.add('btnDel');
    btnDel.classList.add('btn');
    
    btnDel.addEventListener('click' , e =>{
        e.preventDefault();

        const idItem = e.currentTarget.getAttribute('item-id');
        const index = e.currentTarget.getAttribute('i');

        let tab = []

        nbr--;

        console.log(index)
        
        for(let i of tabIndex){
          if(i != index){
              tab.push(i)
          }
        }
        
        tabIndex = [...tab]

        tab = []

        
        removeElementFromDom(idItem);
        removeElementFromList(idItem);
        
    })

    btnDel.innerHTML = `<img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAAqklEQVRIS2NkoDFgpLH5DIQscAA6YD4QK+BwyAOgeCIQH8DlUEIWgAyQJ+BLkBpFci34D9WIyyGE5AkGESEDCMljWADTQGncw32M7nWaWwBzOUGvo3kRp3qyI4/aFqC7kBAfbj+xPiBkIMVBNGoBRr4iNUhG44Bg0URxEBGygWQLPgBN5CdkKpr8Q2w1H66cDKoqFxBRm8HsABmegK3qJFRlkugJTOU0twAAUHk4GewN7TMAAAAASUVORK5CYII="/>`
    
    element.prepend(btnDel);
    element.prepend(hr);
    
    listItem.push(element);
    
    for(let el of listItem){
      div.append(el);
    }

}




function removeElementFromDom(id){
    const item = document.querySelector('[item-id="' + id +'"]')
    div.removeChild(item);
}

function removeElementFromList(id){
  listItem = listItem.filter((item) => {
      item.id !== id
  })
}