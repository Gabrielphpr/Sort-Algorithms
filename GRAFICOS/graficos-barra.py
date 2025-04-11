import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots

def read_sorting_data(filename):
    # Lê o arquivo
    with open(filename, 'r') as file:
        lines = file.readlines()
    
    # Converte as linhas em valores decimais usando float ao invés de int
    data = [list(map(float, line.strip().split(','))) for line in lines]
    
    # Definições
    input_sizes = [100, 1000, 10000, 100000]
    input_types = ['Ordenado', 'Inverso', 'Aleatório']
    algorithms = ['Bubble', 'Count', 'Heap', 'Insertion', 
                 'Merge', 'Quick', 'Radix', 'Selection', 'Shell']
    
    # Cria um DataFrame mais estruturado
    rows = []
    for alg_idx, alg in enumerate(algorithms):
        start_idx = alg_idx * 4
        for size_idx, size in enumerate(input_sizes):
            row_idx = start_idx + size_idx
            row = data[row_idx]
            rows.append({
                'Algoritmo': alg,
                'Tamanho': size,
                'Ordenado': row[0],
                'Inverso': row[1],
                'Aleatório': row[2]
            })
    
    return pd.DataFrame(rows)

def create_visualization(df):
    # Cria uma figura com três subplots
    fig = make_subplots(
        rows=1, cols=3,
        subplot_titles=['Ordenado', 'Inverso', 'Aleatório'],
        horizontal_spacing=0.1
    )
    
    # Cores para cada algoritmo
    colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', 
             '#9467bd', '#8c564b', '#e377c2', '#7f7f7f', '#17becf']
    
    # Tamanhos de entrada como strings para o eixo x
    sizes_str = ['N=100', 'N=1.000', 'N=10.000', 'N=100.000']
    
    input_types = ['Ordenado', 'Inverso', 'Aleatório']
    algorithms = df['Algoritmo'].unique()
    
    # Adiciona barras para cada algoritmo
    for col_idx, input_type in enumerate(input_types, 1):
        for alg_idx, alg in enumerate(algorithms):
            data_slice = df[df['Algoritmo'] == alg]
            
            fig.add_trace(
                go.Bar(
                    name=f'{alg}',
                    x=sizes_str,
                    y=data_slice[input_type],
                    marker_color=colors[alg_idx],
                    showlegend=True if col_idx == 1 else False,
                    # Adiciona formatação para mostrar números decimais nas tooltips
                    hovertemplate="%{y:.3f}<extra></extra>"
                ),
                row=1, col=col_idx
            )
    
    # Atualiza o layout
    fig.update_layout(
        title_text='Comparação de Algoritmos de Ordenação',
        height=600,
        barmode='group',
        legend=dict(
            orientation="h",
            yanchor="bottom",
            y=1.02,
            xanchor="right",
            x=1
        )
    )
    
    # Atualiza os eixos
    for i in range(1, 4):
        fig.update_yaxes(
            title='Comparações' if i == 1 else None,  # Alterado para refletir tempo em segundos
            type='log',
            row=1, 
            col=i,
            tickformat=".3f"  # Formato com 3 casas decimais
        )
        fig.update_xaxes(
            title='Tamanho da Entrada',
            tickangle=45,
            row=1,
            col=i
        )
    
    return fig

def main():
    # Lê os dados
    df = read_sorting_data('comparacoestotal.txt')
    
    # Cria a visualização
    fig = create_visualization(df)
    
    # Salva o gráfico
    fig.write_html('comparacoes_analise.html')
    
    # Mostra o gráfico
    fig.show()

if __name__ == "__main__":
    main()